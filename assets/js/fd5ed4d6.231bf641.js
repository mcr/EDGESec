"use strict";(self.webpackChunkdocusaurus=self.webpackChunkdocusaurus||[]).push([[828],{3905:function(e,t,n){n.d(t,{Zo:function(){return l},kt:function(){return u}});var r=n(7294);function a(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function s(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function i(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?s(Object(n),!0).forEach((function(t){a(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):s(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function o(e,t){if(null==e)return{};var n,r,a=function(e,t){if(null==e)return{};var n,r,a={},s=Object.keys(e);for(r=0;r<s.length;r++)n=s[r],t.indexOf(n)>=0||(a[n]=e[n]);return a}(e,t);if(Object.getOwnPropertySymbols){var s=Object.getOwnPropertySymbols(e);for(r=0;r<s.length;r++)n=s[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(a[n]=e[n])}return a}var c=r.createContext({}),h=function(e){var t=r.useContext(c),n=t;return e&&(n="function"==typeof e?e(t):i(i({},t),e)),n},l=function(e){var t=h(e.components);return r.createElement(c.Provider,{value:t},e.children)},p={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},E=r.forwardRef((function(e,t){var n=e.components,a=e.mdxType,s=e.originalType,c=e.parentName,l=o(e,["components","mdxType","originalType","parentName"]),E=h(n),u=a,d=E["".concat(c,".").concat(u)]||E[u]||p[u]||s;return n?r.createElement(d,i(i({ref:t},l),{},{components:n})):r.createElement(d,i({ref:t},l))}));function u(e,t){var n=arguments,a=t&&t.mdxType;if("string"==typeof e||a){var s=n.length,i=new Array(s);i[0]=E;var o={};for(var c in t)hasOwnProperty.call(t,c)&&(o[c]=t[c]);o.originalType=e,o.mdxType="string"==typeof e?e:a,i[1]=o;for(var h=2;h<s;h++)i[h]=n[h];return r.createElement.apply(null,i)}return r.createElement.apply(null,n)}E.displayName="MDXCreateElement"},7609:function(e,t,n){n.r(t),n.d(t,{frontMatter:function(){return o},contentTitle:function(){return c},metadata:function(){return h},toc:function(){return l},default:function(){return E}});var r=n(7462),a=n(3366),s=(n(7294),n(3905)),i=["components"],o={slug:"capture",title:"Network Capture"},c=void 0,h={unversionedId:"capture",id:"capture",isDocsHomePage:!1,title:"Network Capture",description:"The Network Capture architecture",source:"@site/docs/capture.md",sourceDirName:".",slug:"/capture",permalink:"/EDGESec/docs/capture",editUrl:"https://github.com/nqminds/docusaurus-template/edit/master/docs/capture.md",tags:[],version:"current",frontMatter:{slug:"capture",title:"Network Capture"},sidebar:"someSidebar",previous:{title:"Network Control",permalink:"/EDGESec/docs/control"},next:{title:"Device Discovery",permalink:"/EDGESec/docs/discovery"}},l=[{value:"The Network Capture architecture",id:"the-network-capture-architecture",children:[],level:2},{value:"Packet decoder",id:"packet-decoder",children:[],level:2},{value:"Packet capture",id:"packet-capture",children:[],level:2},{value:"SQLite storer",id:"sqlite-storer",children:[],level:2},{value:"Raw packet storer",id:"raw-packet-storer",children:[],level:2},{value:"GRPC Synchroniser",id:"grpc-synchroniser",children:[],level:2},{value:"Device monitoring",id:"device-monitoring",children:[],level:2}],p={toc:l};function E(e){var t=e.components,n=(0,a.Z)(e,i);return(0,s.kt)("wrapper",(0,r.Z)({},p,n,{components:t,mdxType:"MDXLayout"}),(0,s.kt)("h2",{id:"the-network-capture-architecture"},"The Network Capture architecture"),(0,s.kt)("p",null,"The network capture has the purpose of monitoring network traffic for each connected device. The resulting traffic analytics is sent to the network controller for device management. The network capture contains the following services:"),(0,s.kt)("ul",null,(0,s.kt)("li",{parentName:"ul"},"Packet decoder"),(0,s.kt)("li",{parentName:"ul"},"Packet capture"),(0,s.kt)("li",{parentName:"ul"},"SQLite header storer"),(0,s.kt)("li",{parentName:"ul"},"Raw packet storer"),(0,s.kt)("li",{parentName:"ul"},"GRPC Synchroniser"),(0,s.kt)("li",{parentName:"ul"},"Device monitoring")),(0,s.kt)("p",null,"The capture service is implemented as a standalone executable that can be run on demand by the network controller. The configuration of the capture service is depicted below:"),(0,s.kt)("pre",null,(0,s.kt)("code",{parentName:"pre",className:"language-c"},"struct capture_conf {\n  char capture_interface[IFNAMSIZ];\n  bool promiscuous;\n  bool immediate;\n  uint16_t buffer_timeout;\n  uint16_t process_interval;\n  bool file_write;\n  bool db_write;\n  bool db_sync;\n  char db_path[MAX_OS_PATH_LEN];\n  char db_sync_address[MAX_WEB_PATH_LEN];\n  uint16_t db_sync_port;\n  char *filter;\n};\n")),(0,s.kt)("p",null,"The capture service can be run on a given network interface with a given filter. The capture also has the ability to store the processed packet in SQLite databases or raw format. The databases can be synchronised with the cloud for remote access."),(0,s.kt)("h2",{id:"packet-decoder"},"Packet decoder"),(0,s.kt)("p",null,"The packet decoder extract the metadata from captured packet. The below structure represents all the protocols that are currently being decoded:"),(0,s.kt)("pre",null,(0,s.kt)("code",{parentName:"pre",className:"language-c"},"struct capture_packet {\n  struct ether_header *ethh;\n  struct ether_arp *arph;\n  struct ip *ip4h;\n  struct ip6_hdr *ip6h;\n  struct tcphdr *tcph;\n  struct udphdr *udph;\n  struct icmphdr *icmp4h;\n  struct icmp6_hdr *icmp6h;\n  struct dns_header *dnsh;\n  struct mdns_header *mdnsh;\n  struct dhcp_header *dhcph;\n  uint64_t timestamp;\n  uint32_t caplen;\n  uint32_t length;\n  uint32_t ethh_hash;\n  uint32_t arph_hash;\n  uint32_t ip4h_hash;\n  uint32_t ip6h_hash;\n  uint32_t tcph_hash;\n  uint32_t udph_hash;\n  uint32_t icmp4h_hash;\n  uint32_t icmp6h_hash;\n  uint32_t dnsh_hash;\n  uint32_t mdnsh_hash;\n  uint32_t dhcph_hash;\n  int count;\n};\n")),(0,s.kt)("p",null,"For each decoded packet the service stores the hash of the header as well as the timestamp."),(0,s.kt)("h2",{id:"packet-capture"},"Packet capture"),(0,s.kt)("p",null,"The packet capture implements the actual network sniffing process. Currently it uses pcap library. But it also allow interfacing with PF_RING module that implements zero-copy technique."),(0,s.kt)("h2",{id:"sqlite-storer"},"SQLite storer"),(0,s.kt)("p",null,"The SQLite storer implements the storage process for packet metadata into sqlite databases. Below is the list of schemas created by the SQLite storer that can be used by any application to query the packets:"),(0,s.kt)("pre",null,(0,s.kt)("code",{parentName:"pre"},"CREATE TABLE eth (hash INTEGER NOT NULL, timestamp INTEGER NOT NULL, ethh_hash INTEGER NOT NULL, caplen INTEGER, length INTEGER, ether_dhost TEXT, ether_shost TEXT, ether_type INTEGER,PRIMARY KEY (hash, timestamp, ethh_hash))\nCREATE TABLE arp (hash INTEGER NOT NULL, timestamp INTEGER NOT NULL, ethh_hash INTEGER NOT NULL, caplen INTEGER, length INTEGER, arp_hrd INTEGER, arp_pro INTEGER, arp_hln INTEGER, arp_pln INTEGER, arp_op INTEGER, arp_sha TEXT, arp_spa TEXT, arp_tha TEXT, arp_tpa TEXT, PRIMARY KEY (hash, timestamp, ethh_hash))\nCREATE TABLE ip4 (hash INTEGER NOT NULL, timestamp INTEGER NOT NULL, ethh_hash INTEGER NOT NULL, caplen INTEGER, length INTEGER, ip_hl INTEGER, ip_v INTEGER, ip_tos INTEGER, ip_len INTEGER, ip_id INTEGER, ip_off INTEGER, ip_ttl INTEGER, ip_p INTEGER, ip_sum INTEGER, ip_src TEXT, ip_dst TEXT, PRIMARY KEY (hash, timestamp, ethh_hash))\nCREATE TABLE ip6 (hash INTEGER NOT NULL, timestamp INTEGER NOT NULL, ethh_hash INTEGER NOT NULL, caplen INTEGER, length INTEGER, ip6_un1_flow INTEGER, ip6_un1_plen INTEGER, ip6_un1_nxt INTEGER, cip6_un1_hlim INTEGER, ip6_un2_vfc INTEGER, ip6_src TEXT, ip6_dst TEXT, PRIMARY KEY (hash, timestamp, ethh_hash))\nCREATE TABLE tcp (hash INTEGER NOT NULL, timestamp INTEGER NOT NULL, ethh_hash INTEGER NOT NULL, caplen INTEGER, length INTEGER, source INTEGER, dest INTEGER, seq INTEGER, ack_seq INTEGER, res1 INTEGER, doff INTEGER, fin INTEGER, syn INTEGER, rst INTEGER, psh INTEGER, ack INTEGER, urg INTEGER, window INTEGER, check_p INTEGER, urg_ptr INTEGER, PRIMARY KEY (hash, timestamp, ethh_hash))\nCREATE TABLE udp (hash INTEGER NOT NULL, timestamp INTEGER NOT NULL, ethh_hash INTEGER NOT NULL, caplen INTEGER, length INTEGER, source INTEGER, dest INTEGER, len INTEGER, check_p INTEGER, PRIMARY KEY (hash, timestamp, ethh_hash))\nCREATE TABLE icmp4 (hash INTEGER NOT NULL, timestamp INTEGER NOT NULL, ethh_hash INTEGER NOT NULL, caplen INTEGER, length INTEGER, type INTEGER, code INTEGER, checksum INTEGER, gateway INTEGER, PRIMARY KEY (hash, timestamp, ethh_hash))\nCREATE TABLE icmp6 (hash INTEGER NOT NULL, timestamp INTEGER NOT NULL, ethh_hash INTEGER NOT NULL, caplen INTEGER, length INTEGER, icmp6_type INTEGER, icmp6_code INTEGER, icmp6_cksum INTEGER, icmp6_un_data32 INTEGER, PRIMARY KEY (hash, timestamp, ethh_hash))\nCREATE TABLE dns (hash INTEGER NOT NULL, timestamp INTEGER NOT NULL, ethh_hash INTEGER NOT NULL, caplen INTEGER, length INTEGER, tid INTEGER, flags INTEGER, nqueries INTEGER, nanswers INTEGER, nauth INTEGER, nother INTEGER, PRIMARY KEY (hash, timestamp, ethh_hash))\nCREATE TABLE mdns (hash INTEGER NOT NULL, timestamp INTEGER NOT NULL, ethh_hash INTEGER NOT NULL, caplen INTEGER, length INTEGER, tid INTEGER, flags INTEGER, nqueries INTEGER, nanswers INTEGER, nauth INTEGER, nother INTEGER, PRIMARY KEY (hash, timestamp, ethh_hash))\nCREATE TABLE dhcp (hash INTEGER NOT NULL, timestamp INTEGER NOT NULL, ethh_hash INTEGER NOT NULL, caplen INTEGER, length INTEGER, op INTEGER, htype INTEGER, hlen INTEGER, hops INTEGER, xid INTEGER, secs INTEGER, flags INTEGER, ciaddr TEXT, yiaddr TEXT, siaddr TEXT, giaddr TEXT, PRIMARY KEY (hash, timestamp, ethh_hash))\n")),(0,s.kt)("p",null,"Ever column in the respective table contains the hash of the Ethernet protocol that encapsulated the upper layers of the internet protocol suite as well as the capture timestamp."),(0,s.kt)("h2",{id:"raw-packet-storer"},"Raw packet storer"),(0,s.kt)("p",null,"The raw packet storer stores the raw packet into pcap files and the metadata for each file is stored in a SQLite database. The file name for each packet is randomly generate and subsequently the name is stored in a SQLite database together with the timestamp and packet length. The schema for the SQLite database is depicted below:"),(0,s.kt)("pre",null,(0,s.kt)("code",{parentName:"pre"},"CREATE TABLE meta (id TEXT, timestamp INTEGER NOT NULL, name TEXT, interface TEXT, filter TEXT, caplen INTEGER, length INTEGER, PRIMARY KEY (id, timestamp, interface))\n")),(0,s.kt)("h2",{id:"grpc-synchroniser"},"GRPC Synchroniser"),(0,s.kt)("p",null,"The GRPC syncroniser service implements the syncronisation process to the cloud for stored packet data as well as other tool data. The syncroniser can function in two ways:"),(0,s.kt)("ul",null,(0,s.kt)("li",{parentName:"ul"},"Forward - the syncroniser pushes the tool data to a cloud endpoint"),(0,s.kt)("li",{parentName:"ul"},"Reverse - the syncroniser connects to a cloud endpoint, which subsequently makes a reverse connection to the syncroniser service")),(0,s.kt)("p",null,"The syncronisation process is based on gRPC protocol, where the syncroniser service acts as a client and the cloud endpoint as a server. The connection can be made secure (using TLS) by providing a server certificate."),(0,s.kt)("p",null,"The gRPC protocol uses procol buffers to define the remote execution function. The forward service is implemented by the below protocol buffer:"),(0,s.kt)("pre",null,(0,s.kt)("code",{parentName:"pre"},'syntax = "proto3";\n\npackage sqlite_sync;\n\n// The synchroniser service definition.\nservice Synchroniser {\n  // Registers a db\n  rpc RegisterDb (RegisterDbRequest) returns (RegisterDbReply) {}\n\n  // Synchronise db statement\n  rpc SyncDbStatement (SyncDbStatementRequest) returns (SyncDbStatementReply) {}\n}\n\n// The request message containing the db name and other params.\nmessage RegisterDbRequest {\n  string name = 1;\n}\n\n// The response message containing the registration status\nmessage RegisterDbReply {\n  uint32 status = 1;\n}\n\nmessage SyncDbStatementRequest {\n  string name = 1;\n  string statement = 2;\n}\n\nmessage SyncDbStatementReply {\n  uint32 status = 1;\n}\n')),(0,s.kt)("p",null,"The forward synchroniser is used for cases when one needs to syncronise only the metadata to the cloud. It is implemented as a queue that pushes the packets at given intervals of time."),(0,s.kt)("h2",{id:"device-monitoring"},"Device monitoring"),(0,s.kt)("p",null,"The device monitoring service decodes the network traffic and assembles nettwork flow. Each flow is denoted by a source and destination MAC address, and protcol type. For each flow the device monitoring service calculates a fingerpint using the SHA256 algorithm."),(0,s.kt)("p",null,"The flow results in the following structure:"),(0,s.kt)("pre",null,(0,s.kt)("code",{parentName:"pre",className:"language-c"},"struct nDPI_flow_meta {\n  char src_mac_addr[MACSTR_LEN];\n  char dst_mac_addr[MACSTR_LEN];\n  char protocol[MAX_PROTOCOL_NAME_LEN];\n  char hash[SHA256_HASH_LEN];\n  char query[MAX_QUERY_LEN];\n};\n")),(0,s.kt)("p",null,"where ",(0,s.kt)("strong",{parentName:"p"},"src_mac_addr")," is the source MAC address, ",(0,s.kt)("strong",{parentName:"p"},"dst_mac_addr")," is the destination MAC address, ",(0,s.kt)("strong",{parentName:"p"},"protocol")," is the ID of the identified network protocol, ",(0,s.kt)("strong",{parentName:"p"},"hash")," is the fingerprint of the flow and ",(0,s.kt)("strong",{parentName:"p"},"query")," is the optional query string. The optional ",(0,s.kt)("strong",{parentName:"p"},"query")," string is dependent on the protocol type. For DNS, mDNS and TLS it is the same as the requested host name."),(0,s.kt)("p",null,"Each flow is stored in a sqlite database with teh followinf schema:"),(0,s.kt)("pre",null,(0,s.kt)("code",{parentName:"pre"},"CREATE TABLE fingerprint (mac TEXT NOT NULL, protocol TEXT, fingerprint TEXT, timestamp INTEGER NOT NULL, query TEXT, PRIMARY KEY (mac, timestamp));\n")),(0,s.kt)("p",null,"The timestamp is given as 64 bit microseconds value and the fingerprint string is encoded in base64."),(0,s.kt)("p",null,"An example of the fingerprint table rows are below:"),(0,s.kt)("table",null,(0,s.kt)("thead",{parentName:"table"},(0,s.kt)("tr",{parentName:"thead"},(0,s.kt)("th",{parentName:"tr",align:null},"MACPROTOCOL"),(0,s.kt)("th",{parentName:"tr",align:null},"FINGERPRINT"),(0,s.kt)("th",{parentName:"tr",align:null},"TIMESTAMP"),(0,s.kt)("th",{parentName:"tr",align:null},"QUERY"))),(0,s.kt)("tbody",{parentName:"table"},(0,s.kt)("tr",{parentName:"tbody"},(0,s.kt)("td",{parentName:"tr",align:null},"84:e3:42:3a:cb:2f"),(0,s.kt)("td",{parentName:"tr",align:null},"TLS.Amazon"),(0,s.kt)("td",{parentName:"tr",align:null},"mI1ENXMPBQDVjwGh/o0bLSrD8+O2O5RCFQLbUVt4lzI"),(0,s.kt)("td",{parentName:"tr",align:null},"1625055051481102")),(0,s.kt)("tr",{parentName:"tbody"},(0,s.kt)("td",{parentName:"tr",align:null},"9c:ef:d5:fd:db:56"),(0,s.kt)("td",{parentName:"tr",align:null},"TLS.Amazon"),(0,s.kt)("td",{parentName:"tr",align:null},"mI1ENXMPBQDVjwGh/o0bLSrD8+O2O5RCFQLbUVt4lzI"),(0,s.kt)("td",{parentName:"tr",align:null},"1625055051481102")),(0,s.kt)("tr",{parentName:"tbody"},(0,s.kt)("td",{parentName:"tr",align:null},"84:e3:42:3a:cb:2f"),(0,s.kt)("td",{parentName:"tr",align:null},"DNS"),(0,s.kt)("td",{parentName:"tr",align:null},"NqRTRWiNdfG4zMkiXE9P0eRQIefPgMYV/vXUymxdvNw"),(0,s.kt)("td",{parentName:"tr",align:null},"1625055072748967")),(0,s.kt)("tr",{parentName:"tbody"},(0,s.kt)("td",{parentName:"tr",align:null},"9c:ef:d5:fd:db:56"),(0,s.kt)("td",{parentName:"tr",align:null},"DNS"),(0,s.kt)("td",{parentName:"tr",align:null},"NqRTRWiNdfG4zMkiXE9P0eRQIefPgMYV/vXUymxdvNw"),(0,s.kt)("td",{parentName:"tr",align:null},"1625055072748967")))),(0,s.kt)("p",null,"The entries of the fingerprint table can be queried using the supervisor service."),(0,s.kt)("p",null,"For instance to retrieve all fingerprints for the MAC address 84:e3:42:3a:cb:2f one could use the following command:"),(0,s.kt)("pre",null,(0,s.kt)("code",{parentName:"pre"},"QUERY_FINGERPRINT 84:e3:42:3a:cb:2f 0 >= all\n")),(0,s.kt)("p",null,"To retrieve all the fingerprints up to a given timestamp one could use the following command:"),(0,s.kt)("pre",null,(0,s.kt)("code",{parentName:"pre"},"QUERY_FINGERPRINT 84:e3:42:3a:cb:2f 1625055051481102 <= all\n")),(0,s.kt)("p",null,"To retrieve all the fingerprints for the DNS protocol one could use the following command:"),(0,s.kt)("pre",null,(0,s.kt)("code",{parentName:"pre"},"QUERY_FINGERPRINT 84:e3:42:3a:cb:2f 0 >= DNS\n")))}E.isMDXComponent=!0}}]);