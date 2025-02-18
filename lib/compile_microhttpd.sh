#!/bin/bash

set -e

LIBMICROHTTPD_SOURCE_DIR=$1
LIBMICROHTTPD_INSTALL_DIR=$2/libmicrohttpd
CONFIG_HOST=$3

echo "MICROHTTPD lib source dir: ${LIBMICROHTTPD_SOURCE_DIR}"
echo "MICROHTTPD lib install dir: ${LIBMICROHTTPD_INSTALL_DIR}"
echo "MICROHTTPD lib config host: ${CONFIG_HOST}"

# Set --enable-https to force HTTPS support
# Requires that gnutls is installed
"${LIBMICROHTTPD_SOURCE_DIR}"/configure --prefix="${LIBMICROHTTPD_INSTALL_DIR}" --host="${CONFIG_HOST}" --enable-https

# Load LIB_MAKEFLAGS from CMake if set
export MAKEFLAGS="${MAKEFLAGS-""} ${LIB_MAKEFLAGS-""}"

make
make install
make distclean

