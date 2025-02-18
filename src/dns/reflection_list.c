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
 * @file reflection_list.c
 * @author Alexandru Mereacre 
 * @brief File containing the implementation of reflection list structures.
 */

#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <string.h>

#include "../utils/allocs.h"
#include "../utils/log.h"
#include "../utils/list.h"

#include "reflection_list.h"

void setup_reflection_if_el(struct reflection_list *el, unsigned int ifindex, const char *ifname)
{
  el->recv_fd = -1;
  el->send_fd = -1;
  el->ifindex = ifindex;
  if (ifname == NULL) {
    os_memset(el->ifname, 0, IFNAMSIZ);
  } else {
    snprintf(el->ifname, IFNAMSIZ, "%s", ifname);   
  }
}

struct reflection_list * init_reflection_list(void)
{
  struct reflection_list *rif = os_zalloc(sizeof(struct reflection_list));
  if (rif == NULL) {
    log_err("os_zalloc");
    return NULL;
  }

  setup_reflection_if_el(rif, 0, NULL);
  dl_list_init(&rif->list);

  return rif;
}

struct reflection_list* push_reflection_list(struct reflection_list *rif, unsigned int ifindex, const char *ifname)
{
  struct reflection_list* el;

  if (rif == NULL) {
    log_debug("rif param is NULL");
    return NULL;
  }
  
  if ((el = init_reflection_list()) == NULL) {
    log_debug("init_reflection_list fail");
    return NULL;
  }

  setup_reflection_if_el(el, ifindex, ifname);

  dl_list_add_tail(&rif->list, &el->list);

  return el;
}

struct reflection_list* pop_reflection_list(struct reflection_list *rif)
{
  if (rif == NULL)
    return NULL;

  return dl_list_first(&rif->list, struct reflection_list, list);
}

void free_reflection_list_el(struct reflection_list *el)
{
  if (el != NULL) {
    dl_list_del(&el->list);
	os_free(el);
  }
}

void free_reflection_list(struct reflection_list *rif)
{
  struct reflection_list *el;

  while ((el = pop_reflection_list(rif)) != NULL) {
    free_reflection_list_el(el);
  }

  free_reflection_list_el(rif);  
}