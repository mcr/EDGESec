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
 * @file packet_decoder.h 
 * @author Alexandru Mereacre 
 * @brief File containing the definition of the packet decoder utilities.
 */

#ifndef PACKET_DECODER_H
#define PACKET_DECODER_H

#include <netinet/in.h>
#include <netinet/ip.h>
#include <net/if.h>
#include <netinet/if_ether.h>
#include <netinet/ip6.h>
#include <netinet/ip_icmp.h>
#include <net/ethernet.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <pcap.h>

/**
 * @brief Capturee structure definition
 * 
 */
struct capture_packet {
  struct ether_header *ethh;           /**< Ethernet header.  */
  struct ether_arp *arph;             /**< Embedded ARP header.  */
  struct ip *ip4h;
  struct ip6_hdr *ip6h;
  struct tcphdr *tcph;
  struct udphdr *udph;
  struct icmphdr *icmp4h;
  uint64_t timestamp;
  uint32_t caplen;
  uint32_t length;
  uint32_t ethh_hash;
  uint32_t arph_hash;
  uint32_t ip4h_hash;
  uint32_t ip6h_hash;
  uint32_t tcph_hash;
  uint32_t udph_hash;
};

/**
 * @brief Decodes the packet
 * 
 * @param header The packet header as per pcap
 * @param packet The packet data
 * @return int 0 on success, -1 otherwise
 */
int decode_packet(const struct pcap_pkthdr *header, const u_char *packet);

#endif
