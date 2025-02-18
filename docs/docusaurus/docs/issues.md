---
slug: issues
title: Issues
---

## aclocal-1.15: command not found
```console
cd lib/libmnl-1.0.4
autoreconf -f -i
```

## GRPC/Protobuf linking issues

GRPC is only compatible with certain versions of Protobuf.

Because of this, we recommend that you **only** use GRPC/Protobuf
installed from your system (e.g. in your `apt` repository).

If you have a custom version of GRPC installed in `/usr/local`,
we recommend deleting it, by removing files in:
  - `/usr/local/bin` (e.g. `grpc-cpp-plugin`)
  - `/usr/local/include` (e.g. `grpc++/`)
  - `/usr/local/lib` (e.g. `libgrpc++.so`)
  - `/usr/local/lib/pkgconfig` (e.g. `grpc++.pc`)

You can also compile GRPC and Protobuf from source,
by setting `DBUILD_GRPC_LIB=ON` when running `cmake`.
However, GRPC is difficult to cross-compile, which is why we recommend
using the pre-compiled system version from `apt`.

## "Predictable names" for WiFi interfaces
https://wiki.debian.org/NetworkInterfaceNames#legacy

The scheme detailed above is the new standard default, but there's also a canonical way of overriding the default: you can use .link files to set up naming policies to suit your needs. Thus for instance if you have two PCs each of which has only a single wireless card, but one calls it wlp0s1 and the other wlp1s0, you can arrange for them both to use the name wifi0 to simplify sharing firewall configurations. For details see systemd.link(5).

Here's a relatively futureproof "manual" version of the example given above:

```
 #/etc/systemd/network/10-persistent-net.link
 [Match]
 MACAddress=01:23:45:67:89:ab

 [Link]
 Name=lan0
```

Note: per systemd.link(5), you shouldn't use a name that the kernel might use for another interface (for example "eth0").

It is also possible to reorganize the naming policy by overriding /lib/systemd/network/99-default.link, for instance to insist that all network interfaces are named purely by MAC address:

```
 #/etc/systemd/network/99-default.link
 [Match]
 OriginalName=*

 [Link]
 NamePolicy=mac
 MACAddressPolicy=persistent
```

The folder ```./scripts``` contains the ```predictable_wifi_name.sh``` script to automaticall create the above lik file.

Usage:
```console
sudo ./scripts/predictable_wifi_name.sh source_if_name destination_fi_name
```

## Stop wpa_supplicant listenning on WiFi interfaces (Raspberry Pi case)
Disable the entire wap_supplicant add the below line to ```/etc/dhcpcd.conf```:
```
nohook wpa_supplicant
```

Disable only for a particular wifi interface ```wlanx``` add the below line to ```/etc/dhcpcd.conf```:
```
denyinterfaces wlanx
```
## libmicrohttp TLS

If `libgnutls` and `libcrypt` are not installed, `libmicrohttp` cannot compile
TLS support, and `restsrv` will fail to start.

Because of this, make sure you have the following installed:
(there should now be an error if they are not installed)

```bash
sudo apt-get install libgnutls-dev libgnutls28-dev
```
