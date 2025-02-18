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
 * @file revsrv.cc 
 * @author Alexandru Mereacre 
 * @brief File containing the implementation of the reverse server.
 */

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <mutex>
#include <map>
#include <string_view>
#include <condition_variable>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "reverse_access.grpc.pb.h"

#include "utils/domain.h"
#include "utils/eloop.h"
#include "utils/allocs.h"
#include "utils/os.h"
#include "utils/log.h"
#include "version.h"
#include "revcmd.h"

#define OPT_STRING              ":p:a:c:k:dvh"
#define USAGE_STRING            "\t%s [-p port] [-a path] [-c path] [-k path] [-d] [-h] [-v]"
const char* description_string = R"--(
  NquiringMinds EDGESEC reverse connection server.

  A GRPC synchronization server that lets devices synchonise EDGESEC
  data to the cloud, including both stored packet data as well as other
  tool data.
)--";
#define CONTROL_INTERFACE_NAME  "/tmp/revcontrol"

#define FAIL_RESPONSE           "FAIL"

const std::string METADATA_KEY = "client-id";

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using reverse_access::Reverser;
using reverse_access::CommandRequest;
using reverse_access::CommandReply;
using reverse_access::ResourceRequest;
using reverse_access::ResourceReply;

static __thread char version_buf[10];

struct domain_client_context {
  std::string domain_client_addr;
  int sock;
};

struct client_tuple {
  uint64_t timestamp;
  std::string hostname;
};

// Lock control variables
std::map<std::string, struct domain_client_context> command_mapper;
std::map<std::string, struct client_tuple> client_mapper;
static REVERSE_COMMANDS control_command;
std::string control_command_id;
uint64_t command_client_timestamp;
std::string command_args;

// Lock and conditional variables
std::mutex command_map_lock;
std::mutex client_map_lock;

std::mutex command_lock;
std::condition_variable command_v;

// Lock for logging
std::mutex log_lock;

void lock_fn(bool lock) {
  if (lock)
    log_lock.lock();
  else
    log_lock.unlock();
}

char *get_static_version_string(uint8_t major, uint8_t minor, uint8_t patch)
{
  int ret = snprintf(version_buf, 10, "%d.%d.%d", major, minor, patch);

  if (ret < 0) {
    fprintf(stderr, "snprintf");
    return NULL;
  }

  return version_buf;
}

void show_app_version(void)
{
  fprintf(stdout, "revsrv app version %s\n",
    get_static_version_string(REVSRV_VERSION_MAJOR, REVSRV_VERSION_MINOR,
    REVSRV_VERSION_PATCH));
}

void show_app_help(char *app_name)
{
  show_app_version();
  fprintf(stdout, "Usage:\n");
  fprintf(stdout, USAGE_STRING, basename(app_name));
  fprintf(stdout, "\n%s", description_string);
  fprintf(stdout, "\nOptions:\n");
  fprintf(stdout, "\t-p port\t\t Server port\n");
  fprintf(stdout, "\t-a path\t\t The certificate authority path\n");
  fprintf(stdout, "\t-c path\t\t The certificate path\n");
  fprintf(stdout, "\t-k path\t\t The private key path\n");
  fprintf(stdout, "\t-d\t\t Verbosity level (use multiple -dd... to increase)\n");
  fprintf(stdout, "\t-h\t\t Show help\n");
  fprintf(stdout, "\t-v\t\t Show app version\n\n");
  fprintf(stdout, "Copyright NQMCyber Ltd\n");
  exit(EXIT_SUCCESS);
}

/* Diagnose an error in command-line arguments and terminate the process */
void log_cmdline_error(const char *format, ...)
{
    va_list argList;

    fflush(stdout);           /* Flush any pending stdout */

    fprintf(stdout, "Command-line usage error: ");
    va_start(argList, format);
    vfprintf(stdout, format, argList);
    va_end(argList);

    fflush(stderr);           /* In case stderr is not line-buffered */
    exit(EXIT_FAILURE);
}

int get_port(char *port_str)
{
  if (!is_number(port_str))
    return -1;
  
  return strtol(port_str, NULL, 10);
}

void process_app_options(int argc, char *argv[], int *port, char *key_path,
                         char *cert_path, char *ca_path, uint8_t *verbosity)
{
  int opt;
  int p;

  while ((opt = getopt(argc, argv, OPT_STRING)) != -1) {
    switch (opt) {
    case 'd':
      (*verbosity)++;
      break;
    case 'h':
      show_app_help(argv[0]);
      break;
    case 'v':
      show_app_version();
      exit(EXIT_SUCCESS);
      break;
    case 'p':
      if ((p = get_port(optarg)) < 0) {
        log_cmdline_error("Unrecognized port value -%s\n", optarg);
        exit(EXIT_FAILURE);
      }
      *port = p;
      break;
    case 'k':
      os_strlcpy(key_path, optarg, MAX_OS_PATH_LEN);
      break;
    case 'c':
      os_strlcpy(cert_path, optarg, MAX_OS_PATH_LEN);
      break;
    case 'a':
      os_strlcpy(ca_path, optarg, MAX_OS_PATH_LEN);
      break;
    case ':':
      log_cmdline_error("Missing argument for -%c\n", optopt);
      exit(EXIT_FAILURE);
    case '?':
      log_cmdline_error("Unrecognized option -%c\n", optopt);
      exit(EXIT_FAILURE);
    default: show_app_help(argv[0]);
    }
  }
}

void wait_reverse_command(std::string id, REVERSE_COMMANDS cmd, uint64_t client_timestamp, std::string args)
{
  log_trace("Storing reverse command.");
  {
    std::lock_guard<std::mutex> lk(command_lock);
    control_command_id = id;
    control_command = cmd;
    command_client_timestamp = client_timestamp;
    command_args = args;
  }

  command_v.notify_all();

  log_trace("Wait reverse command...");

  {
    std::unique_lock<std::mutex> lk(command_lock);
    command_v.wait(lk, []{
      return ((control_command == REVERSE_CMD_UNKNOWN) && (!command_client_timestamp));
    });
  }
  log_trace("Processed reverse command.");
}

uint64_t save_client_id(std::string id, std::string hostname)
{
  const std::lock_guard<std::mutex> lock(client_map_lock);
  struct client_tuple tuple;

  os_get_timestamp(&tuple.timestamp);
  tuple.hostname = hostname;
  client_mapper[id] = tuple;

  return tuple.timestamp;
}

void clear_client_id(std:: string id)
{
  const std::lock_guard<std::mutex> lock(client_map_lock);
  client_mapper.erase(id);
}

uint64_t get_client_timestamp(std::string id)
{
  const std::lock_guard<std::mutex> lock(client_map_lock);
  auto found = client_mapper.find(id);
  if (found != client_mapper.end())
    return client_mapper[id].timestamp;

  return 0;
}
std::string find_key_val(const std::multimap<grpc::string_ref, grpc::string_ref> &mapper, std::string key)
{
  for (auto iter = mapper.begin(); iter != mapper.end(); ++iter) {
    const std::string found_key = std::string(iter->first.begin(), iter->first.end());
    if (found_key == key) {
      return std::string(iter->second.begin(), iter->second.end());
    }
  }

  return "";
}

std::string save_domain_context(int sock, std::string domain_client_addr)
{
  struct domain_client_context ctx;
  char rid[MAX_RANDOM_UUID_LEN];
  generate_radom_uuid(rid);
  std::string id(rid);

  const std::lock_guard<std::mutex> lock(command_map_lock);
  ctx.sock =  sock;
  ctx.domain_client_addr = domain_client_addr;
  command_mapper[id] = ctx;

  return id;
}

void clear_domain_context(std::string id)
{
  const std::lock_guard<std::mutex> lock(command_map_lock);
  command_mapper.erase(id);
}

struct domain_client_context get_domain_context(std::string id)
{
  struct domain_client_context ctx;
  const std::lock_guard<std::mutex> lock(command_map_lock);
  ctx.sock = -1;

  for (auto iter = command_mapper.begin(); iter != command_mapper.end(); ++iter) {
    const std::string found_key = std::string(iter->first.begin(), iter->first.end());
    if (found_key == id) {
      return iter->second;
    }
  }

  return ctx;
}

int write_command_data(std::string id, char *buf, ssize_t buf_size)
{
  struct domain_client_context ctx = get_domain_context(id);
  if (ctx.sock>= 0) {
    log_trace("Writing command with id=%s", id.c_str());
    return write_domain_data_s(ctx.sock, buf, buf_size, (char *)(ctx.domain_client_addr).c_str());
  }

  return -1;
}

void clear_command_vars(void)
{
  control_command_id = "";
  control_command = REVERSE_CMD_UNKNOWN;
  command_client_timestamp = 0;
  command_args.clear();
}

ssize_t get_fail_response(char **buf)
{
  ssize_t buf_size = STRLEN(FAIL_RESPONSE) + 1;
  *buf = (char *)os_zalloc(buf_size);

  if (*buf == NULL) {
    log_err("os_zalloc");
    return -1;
  }

  strcpy(*buf, FAIL_RESPONSE);

  return buf_size;
}

class ReverserServiceImpl final : public Reverser::Service {
 public:
  explicit ReverserServiceImpl() {}

  Status SubscribeCommand(ServerContext* context, const CommandRequest* request, ServerWriter<CommandReply>* writer) override {
    const std::multimap<grpc::string_ref, grpc::string_ref> metadata =
      context->client_metadata();

    ssize_t buf_size = 0;
    char *response_buf = NULL;

    const std::string id = find_key_val(metadata, METADATA_KEY);
    const std::string client_hostname = request->hostname();
    uint64_t client_timestamp = save_client_id(id, client_hostname);
    log_trace("Subscribed client with id=%s, timestamp=%llu and hostname=%s", id.c_str(),
              client_timestamp, client_hostname.c_str());

    while(true) {
      CommandReply reply;

      std::unique_lock<std::mutex> lk(command_lock);
      command_v.wait(lk, [client_timestamp]{
        return ((control_command != REVERSE_CMD_UNKNOWN) && (client_timestamp == command_client_timestamp));
      });

      if (context->IsCancelled()) {
        log_trace("Client closed");

        if ((buf_size = get_fail_response(&response_buf)) >= 0 ) {
          log_trace("Sending command to %s", control_command_id.c_str());
          if (write_command_data(control_command_id, response_buf, buf_size) < 0) {
            clear_domain_context(control_command_id);
            log_trace("write_command_data error");
          }
          os_free(response_buf);
        }

        clear_command_vars();

        lk.unlock();
        command_v.notify_all();

        clear_client_id(id);

        return Status::CANCELLED;
      }

      reply.set_id(control_command_id);
      reply.set_command(control_command);
      reply.set_args(command_args);

      writer->Write(reply);

      clear_command_vars();

      lk.unlock();
      command_v.notify_all();
    }

    return Status::OK;
  }

  Status SendResource(ServerContext* context, const ResourceRequest* request, ResourceReply* reply) override {
    const std::multimap<grpc::string_ref, grpc::string_ref> metadata =
      context->client_metadata();

    ssize_t buf_size = 0;
    char *buf = NULL;
    const std::string id = find_key_val(metadata, METADATA_KEY);

    log_trace("Received command %d with id=%s", request->command(), request->id().c_str());

    if (request->command() == REVERSE_CMD_ERROR) {
      buf_size = get_fail_response(&buf);
    } else {
      if ((buf = os_strdup(request->data().c_str())) == NULL) {
        log_err("os_strdup");
        buf_size = get_fail_response(&buf);
      } else {
        buf_size = strlen(buf);
      }
    }

    if (buf == NULL) {
      reply->set_status(1);
    } else {
      log_trace("Sending command to %s", request->id().c_str());
      if (write_command_data(request->id(), buf, buf_size) < 0) {
        reply->set_status(1);
      } else {
        reply->set_status(0);
      }

      os_free(buf);
    }

    clear_domain_context(request->id());

    return Status::OK;
  }

  private:
    std::string meta_;
    mutable std::mutex mtx_;
};

char* process_cmd_str(char *buf, ssize_t len)
{
  char *cmd_line = (char *)os_malloc(len + 1);
  if (cmd_line == NULL) {
    log_err("malloc");
    return NULL;
  }

  os_memcpy(cmd_line, buf, len);
  cmd_line[len] = '\0';

  rtrim(cmd_line, NULL);

  return cmd_line;
}

ssize_t get_client_list_buf(char **buf)
{
  ssize_t buf_size = 0;

  std::string ret;
  const std::lock_guard<std::mutex> lock(client_map_lock);

  for (auto it = client_mapper.begin(); it != client_mapper.end(); ++it) {
    if (it->second.timestamp) {
      ret += it->first + " " + it->second.hostname;
      ret += "\n";
    }
  }

  buf_size = ret.size() + 1;
  *buf = (char *)os_zalloc(buf_size);
  if (*buf == NULL) {
    log_err("os_zalloc");
    return 0;
  }

  os_memcpy(*buf, ret.data(), ret.size());  

  return buf_size;
}

bool is_client(std::string client_id)
{
  const std::lock_guard<std::mutex> lock(client_map_lock);

  for (auto it = client_mapper.begin(); it != client_mapper.end(); ++it) {
    if (it->second.timestamp) {
      if (it->first == client_id) return true;
    }
  }

  return false;
}
int get_client_id(std::string encoded_str, std::string &id)
{
  if (!encoded_str.length()) return -1;
  if (encoded_str[0] != '[') return -1;
  if (encoded_str[encoded_str.length() - 1] != ']') return -1;
  id = encoded_str.substr(1, encoded_str.length() - 2);
  return 0;
}

int process_command(std::vector<std::string> &cmd_list, int sock, std::string domain_client_addr)
{
  ssize_t buf_size = 0;
  uint64_t client_timestamp = 0;
  std::string args;
  char *response_buf = NULL;
  int idx = 2;

  if (cmd_list.size() > 1) {
    std::string encoded_client_id = cmd_list.at(0);
    std::string client_id;
    std::string cmd = cmd_list.at(1);
    std::string domain_client_id = save_domain_context(sock, domain_client_addr);

    if (get_client_id(encoded_client_id, client_id) < 0) {
      log_trace("get_client_id fail");
      buf_size = get_fail_response(&response_buf);
      if (write_command_data(domain_client_id, response_buf, buf_size) < 0) {
        log_trace("write_command_data error");
      }
      clear_domain_context(domain_client_id);
      os_free(response_buf);
      return -1;
    }

    if (client_id.length()) {
      client_timestamp = get_client_timestamp(client_id);

      if (!is_client(client_id)) {
        log_trace("Client %s doesn't exist", client_id.c_str());
        buf_size = get_fail_response(&response_buf);
        if (write_command_data(domain_client_id, response_buf, buf_size) < 0) {
          log_trace("write_command_data error");
        }
        clear_domain_context(domain_client_id);
        os_free(response_buf);
        return -1;
      }
    }

    log_trace("Processing command %s with domain id=%s and client_id=%s", cmd.c_str(),
              domain_client_id.c_str(), client_id.c_str());

    while (idx < cmd_list.size())
      args += cmd_list.at(idx++) + " ";

    if (strcmp(cmd.c_str(), REVERSE_CMD_STR_LIST) == 0 && client_timestamp) {
      wait_reverse_command(domain_client_id, REVERSE_CMD_LIST, client_timestamp, args);
      return 0;
    } else if (strcmp(cmd.c_str(), REVERSE_CMD_STR_CLIENT_EXIT) == 0 && client_timestamp) {
      wait_reverse_command(domain_client_id, REVERSE_CMD_CLIENT_EXIT, client_timestamp, args);
      return 0;
    } else if (strcmp(cmd.c_str(), REVERSE_CMD_STR_GET) == 0 && client_timestamp) {
      wait_reverse_command(domain_client_id, REVERSE_CMD_GET, client_timestamp, args);
      return 0;
    } else if (strcmp(cmd.c_str(), REVERSE_CMD_STR_SQL_EXECUTE) == 0) {
      wait_reverse_command(domain_client_id, REVERSE_CMD_SQL_EXECUTE, client_timestamp, args);
      return 0;
    } else if (strcmp(cmd.c_str(), REVERSE_CMD_STR_LIST_CLIENTS) == 0) {
      buf_size = get_client_list_buf(&response_buf);
    } else {
      log_trace("Unknown command %s", cmd.c_str());
      buf_size = get_fail_response(&response_buf);
    }

    if (response_buf) {
      log_trace("Sending command to %s", domain_client_id.c_str());
      if (write_command_data(domain_client_id, response_buf, buf_size) < 0) {
        clear_domain_context(domain_client_id);
        log_trace("write_command_data error");
        os_free(response_buf);
        return -1;
      }
      os_free(response_buf);
    }

    clear_domain_context(domain_client_id);
  } else {
    return -1;
  }

  return 0;
}

void eloop_read_sock_handler(int sock, void *eloop_ctx, void *sock_ctx)
{
  char *buf, *domain_client_addr, *cmd_line;
  uint32_t bytes_available = 0;
  ssize_t num_bytes;

  if (ioctl(sock, FIONREAD, &bytes_available) == -1) {
    log_err("ioctl");
    return;
  }

  if ((buf = (char*)os_zalloc((size_t)(bytes_available + 1))) == NULL) {
    log_err("os_malloc");
    return;
  }

  if ((domain_client_addr = (char *)os_zalloc(sizeof(struct sockaddr_un))) == NULL) {
    log_err("os_zalloc");
    os_free(buf);
    return;  
  }

  if ((num_bytes = read_domain_data_s(sock, buf, bytes_available, domain_client_addr, 0)) == -1) {
    log_trace("read_domain_data_s fail");
    os_free(buf);
    os_free(domain_client_addr);
  }

  cmd_line = process_cmd_str(buf, num_bytes);
  log_trace("%s", cmd_line);

  std::string cmd_str(cmd_line);
  os_free(cmd_line);

  std::vector<std::string> cmd_list;

  split_string(cmd_list, cmd_str, COMMAND_SEPARATOR);
  if (process_command(cmd_list, sock, domain_client_addr) < 0) {
    log_trace("process_command fail");
  }

  os_free(buf);
  os_free(domain_client_addr);
}

void run_control_socket(std::string &name)
{
  int sock;

  log_info("Control socket at %s", name.c_str());

  if (eloop_init()) {
		log_debug("Failed to initialize event loop");
		return;
	}

  if ((sock = create_domain_server((char *)name.c_str())) == -1) {
    log_trace("create_domain_server fail");
    eloop_destroy();
    return;
  }

  if (eloop_register_read_sock(sock, eloop_read_sock_handler, NULL, NULL) ==  -1) {
    log_trace("eloop_register_read_sock fail");
    eloop_destroy();
    close(sock);
    return;
  }

  log_info("Running event loop");
  eloop_run();

  // close_supervisor(domain_sock);
  eloop_destroy();
}

void run_grpc_server(int port, char *key, char *cert, char *ca)
{
  ReverserServiceImpl reverser;
  std::string server_address("0.0.0.0:");
  server_address += std::to_string(port);

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;

  if (key == NULL && cert == NULL && ca == NULL) {
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    fprintf(stdout, "Configured unsecured connection\n");
  } else {
    grpc::SslServerCredentialsOptions::PemKeyCertPair pkcp = {key, cert};
    grpc::SslServerCredentialsOptions ssl_opts(GRPC_SSL_DONT_REQUEST_CLIENT_CERTIFICATE);
    ssl_opts.pem_root_certs = ca;
    ssl_opts.pem_key_cert_pairs.push_back(pkcp);
    std::shared_ptr<grpc::ServerCredentials> creds = grpc::SslServerCredentials(ssl_opts);
    builder.AddListeningPort(server_address, creds);
    fprintf(stdout, "Configured TLS connection\n");
  }

  builder.RegisterService(&reverser);

  std::unique_ptr<Server> server(builder.BuildAndStart());
  fprintf(stdout, "Server listening on %s", server_address.c_str());

  server->Wait();
}

int main(int argc, char** argv) {
  uint8_t verbosity = 0;
  uint8_t level = 0;
  int port = -1;
  char key_path[MAX_OS_PATH_LEN];
  char cert_path[MAX_OS_PATH_LEN];
  char ca_path[MAX_OS_PATH_LEN];
  char *key = NULL;
  char *cert = NULL;
  char *ca = NULL;

  os_memset(key_path, 0, MAX_OS_PATH_LEN);
  os_memset(cert_path, 0, MAX_OS_PATH_LEN);
  os_memset(ca_path, 0, MAX_OS_PATH_LEN);

  std::string ctrlif(CONTROL_INTERFACE_NAME);

  process_app_options(argc, argv, &port, key_path, cert_path, ca_path, &verbosity); 

  if (optind <= 1) show_app_help(argv[0]);

  if (verbosity > MAX_LOG_LEVELS) {
    level = 0;
  } else if (!verbosity) {
    level = MAX_LOG_LEVELS - 1;
  } else {
    level = MAX_LOG_LEVELS - verbosity;
  }

  // Set the log level
  log_set_level(level);
  log_set_lock(lock_fn);

  if (port <=0 || port > 65535) {
    log_cmdline_error("Unrecognized port value -%d\n", port);
    exit(EXIT_FAILURE);
  }

  fprintf(stdout, "Starting reverse client with:\n");
  fprintf(stdout, "Port --> %d\n", port);
  fprintf(stdout, "Control interface --> %s\n", ctrlif.c_str());
  fprintf(stdout, "Key path --> %s\n", key_path);
  fprintf(stdout, "Cert path --> %s\n", cert_path);
  fprintf(stdout, "Cert authority path --> %s\n", ca_path);

  if (strlen(key_path)) {
    if (read_file_string(key_path, &key) < 0) {
      fprintf(stderr, "read_file_string fail\n");
      exit(1);
    }
  }

  if (strlen(cert_path)) {
    if (read_file_string(cert_path, &cert) < 0) {
      fprintf(stderr, "read_file_string fail\n");
      exit(1);
    }
  }

  if (strlen(ca_path)) {
    if (read_file_string(ca_path, &ca) < 0) {
      fprintf(stderr, "read_file_string fail\n");
      exit(1);
    }
  }

  std::thread control_thread(run_control_socket, std::ref(ctrlif));
  run_grpc_server(port, key, cert, ca);

  if (key != NULL)
    os_free(key);
  if (cert != NULL)
    os_free(cert);
  if (ca != NULL)
    os_free(ca);

  return 0;
}