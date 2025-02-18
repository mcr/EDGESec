#define _GNU_SOURCE

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
#include <setjmp.h>
#include <cmocka.h>

#include "utils/log.h"
#include "dhcp/dnsmasq.h"
#include "dhcp/dhcp_config.h"

static const UT_icd config_dhcpinfo_icd = {sizeof(config_dhcpinfo_t), NULL, NULL, NULL};

static char *test_dhcp_conf_path = "/tmp/dnsmasq-test.conf";
static char *test_dhcp_script_path = "/tmp/dnsmasq_exec-test.sh";
static char *test_dhcp_leasefile_path = "/tmp/dnsmasq.leases";
static char *test_domain_server_path = "/tmp/edgesec-domain-server";
static char *test_dhcp_conf_content =
"no-resolv\n"
"server=8.8.4.4\n"
"server=8.8.8.8\n"
"dhcp-leasefile=/tmp/dnsmasq.leases\n"
"dhcp-script=/tmp/dnsmasq_exec-test.sh\n"
"dhcp-range=wifi_if,10.0.0.2,10.0.0.254,255.255.255.0,24h\n"
"dhcp-range=wifi_if.1,10.0.1.2,10.0.1.254,255.255.255.0,24h\n"
"dhcp-range=wifi_if.2,10.0.2.2,10.0.2.254,255.255.255.0,24h\n"
"dhcp-range=wifi_if.3,10.0.3.2,10.0.3.254,255.255.255.0,24h\n";

static char *test_dhcp_script_content =
"#!/bin/sh\n"
"str=\"SET_IP $1 $2 $3\"\n"
"echo \"Sending $str ...\"\n"
"echo $str | nc -uU /tmp/edgesec-domain-server -w2 -W1\n";

static char *test_dhcp_leasefile_content =
"1635860140 11:22:33:44:55:66 10.0.1.10 pc 11:22:33:44:55:66\n"
"1635860148 44:2a:60:db:f3:91 10.0.1.209 iMac 01:44:2a:60:db:f3:91\n"
"1635860076 1c:bf:ce:17:1f:1c 10.0.2.178 * 01:1c:bf:ce:17:1f:1c\n";

static char *interface="wifi_if";
static char *dns_server="8.8.4.4,8.8.8.8";

bool get_config_dhcpinfo(char *info, config_dhcpinfo_t *el)
{
  UT_array *info_arr;
  utarray_new(info_arr, &ut_str_icd);

  ssize_t count = split_string_array(info, ',', info_arr);
	
  log_trace("Number of substrings=%d", count);

  if (!utarray_len(info_arr))
    goto err;

  char **p = NULL;
  p = (char**) utarray_next(info_arr, p);
  log_trace("vlanid=%s", *p);
  if (*p != NULL) {
    errno = 0;
    el->vlanid = (int) strtol(*p, NULL, 10);
    if (errno == EINVAL)
      goto err;
  } else
    goto err;

  p = (char**) utarray_next(info_arr, p);
  log_trace("ip_addr_low=%s", *p);
  if (*p != NULL) {
    strcpy(el->ip_addr_low, *p);
  } else
    goto err;

  p = (char**) utarray_next(info_arr, p);
  log_trace("ip_addr_upp=%s", *p);
  if (*p != NULL)
    strcpy(el->ip_addr_upp, *p);
  else
    goto err;

  p = (char**) utarray_next(info_arr, p);
  log_trace("subnet_mask=%s", *p);
  if (*p != NULL)
    strcpy(el->subnet_mask, *p);
  else
    goto err;

  p = (char**) utarray_next(info_arr, p);
  log_trace("lease_time=%s", *p);
  if (*p != NULL)
    strcpy(el->lease_time, *p);
  else
    goto err;

  utarray_free(info_arr);
  return true;

err:
  utarray_free(info_arr);
  return false;
}

static void test_generate_dhcp_conf(void **state)
{
  (void) state; /* unused */
  struct dhcp_conf dconf;
  UT_array *server_arr;
  config_dhcpinfo_t el;

  utarray_new(dconf.config_dhcpinfo_array, &config_dhcpinfo_icd);
  utarray_new(server_arr, &ut_str_icd);

  strcpy(dconf.dhcp_conf_path, test_dhcp_conf_path);
  strcpy(dconf.dhcp_script_path, test_dhcp_script_path);
  strcpy(dconf.dhcp_leasefile_path, test_dhcp_leasefile_path);

  assert_true(get_config_dhcpinfo("0,10.0.0.2,10.0.0.254,255.255.255.0,24h", &el));
  utarray_push_back(dconf.config_dhcpinfo_array, &el);
  assert_true(get_config_dhcpinfo("1,10.0.1.2,10.0.1.254,255.255.255.0,24h", &el));
  utarray_push_back(dconf.config_dhcpinfo_array, &el);
  assert_true(get_config_dhcpinfo("2,10.0.2.2,10.0.2.254,255.255.255.0,24h", &el));
  utarray_push_back(dconf.config_dhcpinfo_array, &el);
  assert_true(get_config_dhcpinfo("3,10.0.3.2,10.0.3.254,255.255.255.0,24h", &el));
  utarray_push_back(dconf.config_dhcpinfo_array, &el);

  split_string_array(dns_server, ',', server_arr);

  bool ret = generate_dnsmasq_conf(&dconf, interface, server_arr);
  assert_true(ret);

  FILE *fp = fopen(test_dhcp_conf_path, "r");
  assert_non_null(fp);

  long lSize;
  char * buffer;

  fseek(fp, 0 , SEEK_END);
  lSize = ftell(fp);
  rewind(fp);
  buffer = (char*) malloc(sizeof(char)*lSize);
  assert_non_null(buffer);

  size_t result = fread(buffer, 1, lSize, fp);
  assert_int_equal(result, strlen(test_dhcp_conf_content));
  int cmp = memcmp(buffer, test_dhcp_conf_content, result);
  assert_int_equal(cmp, 0);

  fclose(fp);
  free(buffer);

  utarray_free(server_arr);
  utarray_free(dconf.config_dhcpinfo_array);
}

static void test_generate_script_conf(void **state)
{
  (void) state; /* unused */

  bool ret = generate_dnsmasq_script(test_dhcp_script_path, test_domain_server_path);
  assert_true(ret);

  FILE *fp = fopen(test_dhcp_script_path, "r");
  assert_non_null(fp);

  long lSize;
  char * buffer;

  fseek(fp, 0 , SEEK_END);
  lSize = ftell(fp);
  rewind(fp);
  buffer = (char*) malloc(sizeof(char)*lSize);
  assert_non_null(buffer);

  size_t result = fread(buffer, 1, lSize, fp);
  assert_int_equal(result, strlen(test_dhcp_script_content));
  int cmp = memcmp(buffer, test_dhcp_script_content, result);
  assert_int_equal(cmp, 0);

  fclose(fp);
  free(buffer);
}

static void test_clear_dhcp_lease_entry(void **state)
{
  (void) state; /* unused */
  char *out = NULL;
  FILE *fp = fopen(test_dhcp_leasefile_path, "w");

  assert_non_null(fp);
  fprintf(fp, "%s", test_dhcp_leasefile_content);
  fclose(fp);

  assert_int_equal(clear_dhcp_lease_entry("", test_dhcp_leasefile_path), 0);

  assert_int_equal(clear_dhcp_lease_entry("11:22:33:44:55:66", test_dhcp_leasefile_path), 0);
  assert_int_equal(read_file_string(test_dhcp_leasefile_path, &out), 0);
  assert_null(strstr(out, "11:22:33:44:55:66"));
  assert_non_null(strstr(out, "44:2a:60:db:f3:91"));
  os_free(out);

  assert_int_equal(clear_dhcp_lease_entry("11:22:33:44:55:66", test_dhcp_leasefile_path), 0);
  assert_int_equal(read_file_string(test_dhcp_leasefile_path, &out), 0);
  assert_null(strstr(out, "11:22:33:44:55:66"));
  assert_non_null(strstr(out, "44:2a:60:db:f3:91"));
  os_free(out);

  assert_int_equal(clear_dhcp_lease_entry("44:2a:60:db:f3:91", test_dhcp_leasefile_path), 0);
  assert_int_equal(read_file_string(test_dhcp_leasefile_path, &out), 0);
  assert_null(strstr(out, "44:2a:60:db:f3:91"));
  assert_non_null(strstr(out, "1c:bf:ce:17:1f:1c"));
  os_free(out);

  assert_int_equal(clear_dhcp_lease_entry("1c:bf:ce:17:1f:1c", test_dhcp_leasefile_path), 0);
  assert_int_equal(read_file_string(test_dhcp_leasefile_path, &out), 0);
  assert_null(strstr(out, "1c:bf:ce:17:1f:1c"));
  os_free(out);
}

int main(int argc, char *argv[])
{  
  (void) argc; /* unused */
  (void) argv; /* unused */
  log_set_quiet(false);

  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_generate_dhcp_conf),
    cmocka_unit_test(test_generate_script_conf),
    cmocka_unit_test(test_clear_dhcp_lease_entry)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
