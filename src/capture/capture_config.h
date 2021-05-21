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
 * @file capture_config.h 
 * @author Alexandru Mereacre 
 * @brief File containing the definition of the capture config structures.
 */

#ifndef CAPTURE_CONFIG_H
#define CAPTURE_CONFIG_H

#include <sys/types.h>
#include <net/if.h>
#include <stdbool.h>

#include "../utils/os.h"

typedef enum {
  PACKET_ANALYSER_DEFAULT = 0,
  PACKET_ANALYSER_NDPI = 1,
} PACKET_ANALYSER_ENGINE;
/**
 * @brief The capture configuration structure
 * 
 */
struct capture_conf {
  char capture_interface[IFNAMSIZ];                           /**< The capture interface name (any - to capture on all interfaces) */
  bool promiscuous;                                           /**< Specifies whether the interface is to be put into promiscuous mode. If promiscuous param is non-zero, promiscuous mode will be set, otherwise it will not be set */
  bool immediate;                                             /**< Sets whether immediate mode should be set on a capture handle when the handle is activated. If immediate param is non-zero, immediate mode will be set, otherwise it will not be set. */
  uint16_t buffer_timeout;                                    /**< Specifies the packet buffer timeout, as a non-negative value, in milliseconds. (See pcap(3PCAP) for an explanation of the packet buffer timeout.) */
  uint16_t process_interval;                                  /**< Specifies the packet process interval, in milliseconds. */ 
  PACKET_ANALYSER_ENGINE analyser;                            /**< Specifies the packet analyser engine. */ 
  bool file_write;                                            /**< Specifies wether the packets should be saved to file(s). */
  bool db_write;                                              /**< Specifies wether the packets should be saved in a sqlite db. */
  bool db_sync;                                               /**< Specifies wether the packets db should be synced. */
  char db_path[MAX_OS_PATH_LEN];                              /**< Specifies the path to the sqlite3 dbs */ 
  char db_sync_address[MAX_WEB_PATH_LEN];                     /**< Specifies the web address for sqlite syncing */
  uint16_t db_sync_port;                                      /**< Specifies the port of the web address for sqlite syncing */
  char *filter;                                               /**< Specifies the filter expression or pcap lib */
};

#endif