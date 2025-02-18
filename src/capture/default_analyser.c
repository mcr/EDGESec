/****************************************************************************
 * Copyright (C) 2021 by NQMCyber Ltd                                       *
 *                                                                          *
 * This file is part of EDGESec.                                            *
 *                                                                          *
 *   EDGESec is free software: you can redistribute it and/or modify it     *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   EDGESec is distributed in the hope that it will be useful,             *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with EDGESec. If not, see <http://www.gnu.org/licenses/>.*
 ****************************************************************************/
/**
 * @file default_analyser.c
 * @author Alexandru Mereacre 
 * @brief File containing the implementation of the default analyser service.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <errno.h>
#include <net/if.h>
#include <libgen.h>
#include <pcap.h>

#include "default_analyser.h"
#include "capture_config.h"
#include "packet_decoder.h"
#include "packet_queue.h"
#include "pcap_queue.h"
#include "pcap_service.h"
#include "sqlite_header_writer.h"
#include "sqlite_pcap_writer.h"

#include "../utils/domain.h"
#include "../utils/squeue.h"
#include "../utils/if.h"
#include "../utils/log.h"
#include "../utils/eloop.h"
#include "../utils/list.h"
#include "../utils/allocs.h"
#include "../utils/os.h"

#ifdef WITH_SQLSYNC_SERVICE
uint32_t run_register_db(char *ca, char *address, char *name);
uint32_t run_sync_db_statement(char *ca, char *address, char *name, bool default_db, char *statement);
#endif

static const UT_icd tp_list_icd = {sizeof(struct tuple_packet), NULL, NULL, NULL};

// static const UT_icd pcap_context_icd = {sizeof(struct pcap_context*), NULL, NULL, NULL};

void construct_header_db_name(char *name, char *db_name)
{
  strcat(db_name, name);
  strcat(db_name, SQLITE_EXTENSION);
}

void construct_pcap_file_name(char *file_name)
{
  generate_radom_uuid(file_name);
  strcat(file_name, PCAP_EXTENSION);
}

void add_packet_queue(struct capture_context *context, UT_array *tp_array, struct packet_queue *queue)
{
  struct tuple_packet *p = NULL;

  while((p = (struct tuple_packet *) utarray_next(tp_array, p)) != NULL) {
    if (context->db_write) {
      if (push_packet_queue(queue, *p) == NULL) {
        log_trace("push_packet_queue fail");
        // Free the packet if cannot be added to the queue
        free_packet_tuple(p);
      }
    }
  }
}

void pcap_callback(const void *ctx, const void *pcap_ctx,
                   char *ltype, struct pcap_pkthdr *header, uint8_t *packet)
{
  struct capture_context *context = (struct capture_context *)ctx;
  struct pcap_context *pc = (struct pcap_context *) pcap_ctx;

  UT_array *tp_array = NULL;

  utarray_new(tp_array, &tp_list_icd);
  if (extract_packets(ltype, header, packet, pc->ifname,
                      context->hostname, context->cap_id, tp_array) > 0) {
    add_packet_queue(context, tp_array, context->pqueue);
  }

  utarray_free(tp_array);

  if (context->file_write) {
    if (push_pcap_queue(context->cqueue, header, packet) == NULL) {
      log_trace("push_pcap_queue fail");
    } else {
      log_trace("Pushed packet size=%d", header->caplen);
    }
  }
}

void eloop_read_fd_handler(int sock, void *eloop_ctx, void *sock_ctx)
{
  (void) sock;
  (void) sock_ctx;
  struct pcap_context *pc = (struct pcap_context *) eloop_ctx;

  if (capture_pcap_packet(pc) < 0) {
    log_trace("capture_pcap_packet fail");
  }
}

int save_pcap_file_data(struct pcap_pkthdr *header, uint8_t *packet,
                        struct capture_context *context, struct pcap_context *pc)
{
  char *path = NULL;
  char file_name[MAX_PCAP_FILE_NAME_LENGTH];
  uint64_t timestamp = 0;

  os_to_timestamp(header->ts, &timestamp);
  construct_pcap_file_name(file_name);

  if ((path = construct_path(context->pcap_path, file_name)) == NULL) {
    log_trace("construct_path fail");
    return -1;
  }

  if (dump_file_pcap(pc, path, header, packet) < 0) {
    log_trace("dump_file_pcap fail");
    os_free(path);
    return -1;
  }

  os_free(path);

  if (save_sqlite_pcap_entry(context->pcap_db, file_name, timestamp,
        header->caplen, header->len, pc->ifname, context->filter) < 0) {
    log_trace("save_sqlite_pcap_entry fail");
    return -1;
  }

  return 0;
}

void eloop_tout_handler(void *eloop_ctx, void *user_ctx)
{
  struct pcap_context *pc = (struct pcap_context *) eloop_ctx;
  struct capture_context *context = (struct capture_context *) user_ctx;
  struct packet_queue *el_packet;
  struct pcap_queue *el_pcap;
  char *traces = NULL;

  // Process all packets in the queue
  while(is_packet_queue_empty(context->pqueue) < 1) {
    if ((el_packet = pop_packet_queue(context->pqueue)) != NULL) {
      if (context->db_write) {
        save_packet_statement(context->header_db, &(el_packet->tp));
      }
      free_packet_tuple(&el_packet->tp);
      free_packet_queue_el(el_packet);
    }
  }

  if (context->file_write) {
    while(is_pcap_queue_empty(context->cqueue) < 1) {
      if ((el_pcap = pop_pcap_queue(context->cqueue)) != NULL) {
        if (save_pcap_file_data(&(el_pcap->header), el_pcap->packet, context, pc) < 0) {
          log_trace("save_pcap_file_data fail");
        }
        free_pcap_queue_el(el_pcap);
      }
    }
  }

  if (context->db_sync) {
    if ((traces = concat_string_queue(context->squeue, context->sync_send_size)) != NULL) {
#ifdef WITH_SQLSYNC_SERVICE
      if (!run_sync_db_statement(context->ca, context-> grpc_srv_addr, context->db_name, 1, traces)) {
        log_trace("run_sync_db_statement fail");
      }
#endif
      os_free(traces);
      empty_string_queue(context->squeue, context->sync_send_size);
    }
  }

  if (eloop_register_timeout(0, context->process_interval, eloop_tout_handler, (void *) eloop_ctx, (void *) user_ctx) == -1) {
    log_debug("eloop_register_timeout fail");
  }
}

void trace_callback(char *sqlite_statement, void *ctx)
{
  struct string_queue *squeue = (struct string_queue *)ctx;

  if (push_string_queue(squeue, sqlite_statement) < 0) {
    log_trace("push_string_queue fail");
  }
}

int start_default_analyser(struct capture_conf *config)
{
  int ret = -1;
  struct capture_context context;
  struct pcap_context *pc = NULL;
  char *header_db_path = NULL;
  char *pcap_db_path = NULL;
  char *pcap_subfolder_path = NULL;

  os_memset(&context, 0, sizeof(context));

  if ((pcap_subfolder_path = construct_path(config->db_path, PCAP_SUBFOLDER_NAME)) == NULL) {
    log_trace("construct_path fail");
    return -1;
  }

  strcpy(context.pcap_path, pcap_subfolder_path);
  os_free(pcap_subfolder_path);

  if (create_dir(context.pcap_path, S_IRWXU | S_IRWXG) < 0) {
    log_debug("create_dir fail");
    return -1;
  }

  generate_radom_uuid(context.cap_id);

  if (get_hostname(context.hostname) < 0) {
    log_debug("get_hostname fail");
    return -1;
  }
  // Transform to microseconds
  context.filter = config->filter;
  context.process_interval = config->process_interval * 1000;
  context.buffer_timeout = config->buffer_timeout;
  context.promiscuous = config->promiscuous;
  context.immediate = config->immediate;
  context.file_write = config->file_write;
  context.db_write = config->db_write;
  context.db_sync = config->db_sync;
  context.db_path = config->db_path;
  context.sync_store_size = config->sync_store_size;
  context.sync_send_size = config->sync_send_size;
  context.domain_delim = config->domain_delim;

  os_strlcpy(context.domain_command, config->domain_command, MAX_SUPERVISOR_CMD_SIZE);
  os_strlcpy(context.domain_server_path, config->domain_server_path, MAX_OS_PATH_LEN);

  if (strlen(config->db_sync_address)) {
    snprintf(context.grpc_srv_addr, MAX_WEB_PATH_LEN, "%s:%d", config->db_sync_address, config->db_sync_port);
  }

  construct_header_db_name(context.cap_id, context.db_name);
  if ((header_db_path = construct_path(context.db_path, context.db_name)) == NULL) {
    log_debug("construct_path fail");
    return -1;
  }

  if ((pcap_db_path = construct_path(context.db_path, PCAP_DB_NAME)) == NULL) {
    log_debug("construct_path fail");
    os_free(header_db_path);
    return -1;
  }
  
  if (os_strnlen_s(config->ca_path, MAX_OS_PATH_LEN) && context.db_sync) {
      if (read_file_string(config->ca_path, &context.ca) < 0) {
        os_free(header_db_path);
        os_free(pcap_db_path);
        return -1;
      }
  }

  log_info("Capturing hostname=%s", context.hostname);
  log_info("Capturing id=%s", context.cap_id);
  log_info("Capturing pcap_path=%s", context.pcap_path);
  log_info("Capturing interface(s)=%s", config->capture_interface);
  log_info("Capturing filter=%s", context.filter);
  log_info("Promiscuous mode=%d", context.promiscuous);
  log_info("Immediate mode=%d", context.immediate);
  log_info("Buffer timeout=%d", context.buffer_timeout);
  log_info("Process interval=%d (milliseconds)", context.process_interval);
  log_info("Sync store size=%ld",   context.sync_store_size);
  log_info("Sync send size=%ld",   context.sync_send_size);
  log_info("File write=%d", context.file_write);
  log_info("DB write=%d", context.db_write);
  log_info("DB sync=%d", context.db_sync);
  log_info("DB name=%s", context.db_name);
  log_info("DB path=%s", header_db_path);
  log_info("GRPC Server address=%s", context.grpc_srv_addr);
  log_info("GRPC Sync CA path=%s", config->ca_path);
  log_info("Supervisor command=%s", context.domain_command);
  log_info("Supervisor delim=%d", context.domain_delim);
  log_info("Domain path=%s", context.domain_server_path);

  context.pqueue = init_packet_queue();

  if (context.pqueue == NULL) {
    log_debug("init_packet_queue fail");
    if (context.ca != NULL) os_free(context.ca);
    os_free(header_db_path);
    os_free(pcap_db_path);
    return -1;
  }

  context.cqueue = init_pcap_queue();

  if (context.cqueue == NULL) {
    log_debug("init_pcap_queue fail");
    if (context.ca != NULL) os_free(context.ca);
    os_free(header_db_path);
    os_free(pcap_db_path);
    free_packet_queue(context.pqueue);
    return -1;
  }

  context.squeue = init_string_queue(context.sync_store_size);
  if (context.squeue == NULL) {
    log_debug("init_string_queue fail");
    if (context.ca != NULL) os_free(context.ca);
    free_packet_queue(context.pqueue);
    free_pcap_queue(context.cqueue);
    os_free(header_db_path);
    os_free(pcap_db_path);
    return -1;
  }

  if (context.db_write) {
    if (context.db_sync) {
#ifdef WITH_SQLSYNC_SERVICE
      if (!run_register_db(context.ca, context.grpc_srv_addr, context.db_name)) {
        log_trace("run_register_db fail");
      }
      ret = open_sqlite_header_db(header_db_path, trace_callback, (void*)context.squeue, &context.header_db);
#else
      ret = open_sqlite_header_db(header_db_path, NULL, NULL, &context.header_db);
#endif
    } else {
      ret = open_sqlite_header_db(header_db_path, NULL, NULL, &context.header_db);
    }

    if (ret < 0) {
      log_debug("open_sqlite_header_db fail");
      if (context.ca != NULL) os_free(context.ca);
      free_packet_queue(context.pqueue);
      free_pcap_queue(context.cqueue);
      free_string_queue(context.squeue);
      os_free(header_db_path);
      os_free(pcap_db_path);
      return -1;
    }
  }

  if (context.file_write) {
    if (open_sqlite_pcap_db(pcap_db_path, (sqlite3**)&context.pcap_db) < 0) {
      log_debug("open_sqlite_pcap_db fail");
      if (context.ca != NULL) os_free(context.ca);
      free_packet_queue(context.pqueue);
      free_pcap_queue(context.cqueue);
      free_string_queue(context.squeue);
      os_free(header_db_path);
      os_free(pcap_db_path);
      free_sqlite_header_db(context.header_db);
      return -1;
    }
  }

  if (eloop_init()) {
		log_debug("Failed to initialize event loop");
    goto fail;
	}

  log_info("Registering pcap for ifname=%s", config->capture_interface);
  if (run_pcap(config->capture_interface, context.immediate,
               context.promiscuous, (int)context.buffer_timeout,
               context.filter, true, pcap_callback, (void *)&context, &pc) < 0) {
    log_debug("run_pcap fail");
    goto fail;
  }

  if (pc != NULL) {
    if (eloop_register_read_sock(pc->pcap_fd, eloop_read_fd_handler, (void*) pc, (void *) NULL) ==  -1) {
      log_debug("eloop_register_read_sock fail");
      goto fail;
    }
  } else {
    log_debug("Empty pcap context");
    goto fail;
  }

  if (eloop_register_timeout(0, context.process_interval, eloop_tout_handler, (void *) pc, (void *)&context) == -1) {
    log_debug("eloop_register_timeout fail");
    goto fail;
  }


  eloop_run();
  log_info("Capture ended.");

	/* And close the session */
  close_pcap(pc);
  if (context.ca != NULL) {
    os_free(context.ca);
  }
  eloop_destroy();
  free_packet_queue(context.pqueue);
  free_pcap_queue(context.cqueue);
  free_string_queue(context.squeue);
  free_sqlite_header_db(context.header_db);
  free_sqlite_pcap_db(context.pcap_db);
  os_free(header_db_path);
  os_free(pcap_db_path);
  return 0;

fail:
  close_pcap(pc);
  if (context.ca != NULL) {
    os_free(context.ca);
  }
  eloop_destroy();
  free_packet_queue(context.pqueue);
  free_pcap_queue(context.cqueue);
  free_string_queue(context.squeue);
  free_sqlite_header_db(context.header_db);
  free_sqlite_pcap_db(context.pcap_db);
  os_free(header_db_path);
  os_free(pcap_db_path);
  return -1;
}
