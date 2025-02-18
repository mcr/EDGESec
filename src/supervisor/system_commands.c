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
 * @file system_commands.c
 * @author Alexandru Mereacre 
 * @brief File containing the implementation of the system commands.
 */
#include <sys/un.h>
#include <libgen.h>

#include "system_commands.h"
#include "mac_mapper.h"
#include "supervisor.h"
#include "sqlite_fingerprint_writer.h"
#include "sqlite_macconn_writer.h"
#include "network_commands.h"
#include "subscriber_events.h"

#include "../ap/ap_config.h"
#include "../ap/ap_service.h"
#include "../crypt/crypt_service.h"
#include "../capture/capture_service.h"
#include "../utils/allocs.h"
#include "../utils/os.h"
#include "../utils/log.h"
#include "../utils/base64.h"
#include "../utils/eloop.h"
#include "../utils/iptables.h"
#include "../utils/domain.h"
#include "../utils/utarray.h"

#define PING_REPLY  "PONG"

int set_ip_cmd(struct supervisor_context *context, uint8_t *mac_addr,
  char *ip_addr, enum DHCP_IP_TYPE ip_type)
{
  UT_array *mac_list_arr;
  uint8_t *p = NULL;
  char ifname[IFNAMSIZ];
  struct mac_conn conn;
  struct mac_conn_info right_info, info;
  int ret;
  bool add = (ip_type == DHCP_IP_NEW || ip_type == DHCP_IP_OLD);

  init_default_mac_info(&info, context->default_open_vlanid, context->allow_all_nat);

  if (!get_ifname_from_ip(&context->if_mapper, context->config_ifinfo_array, ip_addr, ifname)) {
    log_trace("get_ifname_from_ip fail");
    return -1;
  }

  ret = get_mac_mapper(&context->mac_mapper, mac_addr, &info);
  if (ret < 0) {
    log_trace("get_mac_mapper fail");
    return -1;
  }

  switch(ip_type) {
    case DHCP_IP_NEW:
    case DHCP_IP_OLD:
      if (strcmp(info.ip_addr, ip_addr) == 0) {
        log_trace("IP %s already assigned as primary", ip_addr);
        return 0;
      } else if (strcmp(info.ip_sec_addr, ip_addr) == 0) {
        log_trace("IP %s already assigned as secondary", ip_addr);
        return 0;
      }

      if (!strlen(info.ip_addr)) {
        os_strlcpy(info.ip_addr, ip_addr, IP_LEN);
      } else if (strlen(info.ip_addr) && !strlen(info.ip_sec_addr)) {
        os_strlcpy(info.ip_sec_addr, ip_addr, IP_LEN);
      } else {
        log_trace("IPs already present");
        return -1;
      }
      break;
    case DHCP_IP_DEL:
      if (strcmp(info.ip_addr, ip_addr) == 0) {
        os_memset(info.ip_addr, 0x0, IP_LEN);
      }

      if (strcmp(info.ip_sec_addr, ip_addr) == 0) {
        os_memset(info.ip_sec_addr, 0, IP_LEN);
      }
      break;
    default:
      log_trace("Wrong DHCP IP type");
      return -1;
  }

  os_memcpy(info.ifname, ifname, IFNAMSIZ);
  os_memcpy(conn.mac_addr, mac_addr, ETH_ALEN);
  os_memcpy(&conn.info, &info, sizeof(struct mac_conn_info));

  log_trace("SET_IP type=%d mac=" MACSTR " ip=%s if=%s", ip_type, MAC2STR(mac_addr), ip_addr, ifname);
  if (!save_mac_mapper(context, conn)) {
    log_trace("save_mac_mapper fail");
    return -1;
  }

  if (send_events_subscriber(context, SUBSCRIBER_EVENT_IP, MACSTR" %s %d",
                             MAC2STR(mac_addr), ip_addr, add) < 0) {
    log_trace("send_events_subscriber fail");
    return -1;
  }

  // Change the NAT iptables rules
  if (add && info.nat) {
    log_trace("Adding NAT rule");
    if (add_nat_ip(context, ip_addr) < 0) {
      log_trace("add_nat_ip fail");
      return -1;
    }
  } else if (!add && info.nat){
    log_trace("Deleting NAT rule");
    if (remove_nat_ip(context, ip_addr) < 0) {
      log_trace("remove_nat_ip fail");
      return -1;
    }
  }

  // Change the bridge iptables rules
  // Get the list of all dst MACs to update the iptables
  if(get_src_mac_list(context->bridge_list, mac_addr, &mac_list_arr) < 0) {
    log_trace("get_src_mac_list fail");
    return -1;
  }

  while((p = (uint8_t *) utarray_next(mac_list_arr, p)) != NULL) {
    if(get_mac_mapper(&context->mac_mapper, p, &right_info) == 1) {
      if (add) {
        if (add_bridge_ip(context, ip_addr, right_info.ip_addr) < 0) {
          log_trace("add_bridge_ip fail");
          utarray_free(mac_list_arr);
          return -1;
        }
        if (add_bridge_ip(context, ip_addr, right_info.ip_sec_addr) < 0) {
          log_trace("add_bridge_ip fail");
          utarray_free(mac_list_arr);
          return -1;
        }
      } else {
        if (delete_bridge_ip(context, ip_addr, right_info.ip_addr) < 0) {
          log_trace("delete_bridge_ip fail");
          utarray_free(mac_list_arr);
          return -1;
        }
        if (delete_bridge_ip(context, ip_addr, right_info.ip_sec_addr) < 0) {
          log_trace("delete_bridge_ip fail");
          utarray_free(mac_list_arr);
          return -1;
        }
      }
    }
  }

  utarray_free(mac_list_arr);
  return 0;
}

char* ping_cmd(void)
{
  return os_strdup(PING_REPLY);
}

int subscribe_events_cmd(struct supervisor_context *context, struct client_address *addr)
{
  log_trace("SUBSCRIBE_EVENTS with size=%d", addr->len);
  return add_events_subscriber(context, addr);
}