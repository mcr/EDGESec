/**************************************************************************************************
*  Filename:        hashmap.c
*  Author:          Alexandru Mereacre (mereacre@gmail.com)
*  Revised:
*  Revision:
*
*  Description:     hashmap source file
*
*  Copyright (C) 2020 NQMCyber Ltd - http://www.nqmcyber.com/
*************************************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "os.h"
#include "log.h"
#include "hashmap.h"
#include "uthash.h"

hmap_str_keychar *hmap_str_keychar_new(void)
{
	return NULL;
}

char *hmap_str_keychar_get(hmap_str_keychar **hmap, char *keyptr)
{
	hmap_str_keychar *s;

	if(keyptr == NULL) {
		log_trace("keyptr is NULL");
		return NULL;
	}

	HASH_FIND_STR(*hmap, keyptr, s);

	if (s != NULL)
		return s->value;

	return NULL;
}

bool hmap_str_keychar_put(hmap_str_keychar **hmap, char *keyptr, char *value)
{
	hmap_str_keychar *s;

	if (keyptr == NULL) {
		log_trace("keyptr is NULL");
		return false;
	}

	if (strlen(keyptr) > HASH_KEY_CHAR_SIZE - 1) {
		log_trace("strlen(keyptr) is greater than key char size");
		return false;
	}

	HASH_FIND_STR(*hmap, keyptr, s); /* id already in the hash? */

  if (s == NULL) {
    s = (hmap_str_keychar *) os_malloc(sizeof(hmap_str_keychar));
		if (s == NULL) {
			log_err_ex("os_malloc");
		}

		// Copy the key
		strcpy(s->key, keyptr);
		s->value = allocate_string(value);

		HASH_ADD_STR(*hmap, key, s);
  } else {
		// Copy the value
		os_free(s->value);
    s->value = allocate_string(value);
	}

	return true;
}

void hmap_str_keychar_free(hmap_str_keychar **hmap)
{
	hmap_str_keychar *current, *tmp;

	HASH_ITER(hh, *hmap, current, tmp) {
    HASH_DEL(*hmap, current);  							/* delete it (users advances to next) */
		os_free(current->value);								/* free the value content */
    os_free(current);            						/* free it */
  }
}