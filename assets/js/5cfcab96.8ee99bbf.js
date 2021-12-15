"use strict";(self.webpackChunkdocusaurus=self.webpackChunkdocusaurus||[]).push([[566],{3905:function(e,n,t){t.d(n,{Zo:function(){return p},kt:function(){return m}});var i=t(7294);function r(e,n,t){return n in e?Object.defineProperty(e,n,{value:t,enumerable:!0,configurable:!0,writable:!0}):e[n]=t,e}function a(e,n){var t=Object.keys(e);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);n&&(i=i.filter((function(n){return Object.getOwnPropertyDescriptor(e,n).enumerable}))),t.push.apply(t,i)}return t}function l(e){for(var n=1;n<arguments.length;n++){var t=null!=arguments[n]?arguments[n]:{};n%2?a(Object(t),!0).forEach((function(n){r(e,n,t[n])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(t)):a(Object(t)).forEach((function(n){Object.defineProperty(e,n,Object.getOwnPropertyDescriptor(t,n))}))}return e}function o(e,n){if(null==e)return{};var t,i,r=function(e,n){if(null==e)return{};var t,i,r={},a=Object.keys(e);for(i=0;i<a.length;i++)t=a[i],n.indexOf(t)>=0||(r[t]=e[t]);return r}(e,n);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);for(i=0;i<a.length;i++)t=a[i],n.indexOf(t)>=0||Object.prototype.propertyIsEnumerable.call(e,t)&&(r[t]=e[t])}return r}var s=i.createContext({}),c=function(e){var n=i.useContext(s),t=n;return e&&(t="function"==typeof e?e(n):l(l({},n),e)),t},p=function(e){var n=c(e.components);return i.createElement(s.Provider,{value:n},e.children)},u={inlineCode:"code",wrapper:function(e){var n=e.children;return i.createElement(i.Fragment,{},n)}},d=i.forwardRef((function(e,n){var t=e.components,r=e.mdxType,a=e.originalType,s=e.parentName,p=o(e,["components","mdxType","originalType","parentName"]),d=c(t),m=r,f=d["".concat(s,".").concat(m)]||d[m]||u[m]||a;return t?i.createElement(f,l(l({ref:n},p),{},{components:t})):i.createElement(f,l({ref:n},p))}));function m(e,n){var t=arguments,r=n&&n.mdxType;if("string"==typeof e||r){var a=t.length,l=new Array(a);l[0]=d;var o={};for(var s in n)hasOwnProperty.call(n,s)&&(o[s]=n[s]);o.originalType=e,o.mdxType="string"==typeof e?e:r,l[1]=o;for(var c=2;c<a;c++)l[c]=t[c];return i.createElement.apply(null,l)}return i.createElement.apply(null,t)}d.displayName="MDXCreateElement"},2186:function(e,n,t){t.r(n),t.d(n,{frontMatter:function(){return o},contentTitle:function(){return s},metadata:function(){return c},toc:function(){return p},default:function(){return d}});var i=t(7462),r=t(3366),a=(t(7294),t(3905)),l=["components"],o={slug:"issues",title:"Issues"},s=void 0,c={unversionedId:"issues",id:"issues",isDocsHomePage:!1,title:"Issues",description:"aclocal-1.15: command not found",source:"@site/docs/issues.md",sourceDirName:".",slug:"/issues",permalink:"/EDGESec/docs/issues",editUrl:"https://github.com/nqminds/docusaurus-template/edit/master/docs/issues.md",tags:[],version:"current",frontMatter:{slug:"issues",title:"Issues"},sidebar:"someSidebar",previous:{title:"Creating a .deb",permalink:"/EDGESec/docs/deb"},next:{title:"Supported Devices",permalink:"/EDGESec/docs/devices"}},p=[{value:"aclocal-1.15: command not found",id:"aclocal-115-command-not-found",children:[],level:2},{value:"GRPC/Protobuf linking issues",id:"grpcprotobuf-linking-issues",children:[],level:2},{value:"&quot;Predictable names&quot; for WiFi interfaces",id:"predictable-names-for-wifi-interfaces",children:[],level:2},{value:"Stop wpa_supplicant listenning on WiFi interfaces (Raspberry Pi case)",id:"stop-wpa_supplicant-listenning-on-wifi-interfaces-raspberry-pi-case",children:[],level:2},{value:"libmicrohttp TLS",id:"libmicrohttp-tls",children:[],level:2}],u={toc:p};function d(e){var n=e.components,t=(0,r.Z)(e,l);return(0,a.kt)("wrapper",(0,i.Z)({},u,t,{components:n,mdxType:"MDXLayout"}),(0,a.kt)("h2",{id:"aclocal-115-command-not-found"},"aclocal-1.15: command not found"),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre",className:"language-console"},"cd lib/libmnl-1.0.4\nautoreconf -f -i\n")),(0,a.kt)("h2",{id:"grpcprotobuf-linking-issues"},"GRPC/Protobuf linking issues"),(0,a.kt)("p",null,"GRPC is only compatible with certain versions of Protobuf."),(0,a.kt)("p",null,"Because of this, we recommend that you ",(0,a.kt)("strong",{parentName:"p"},"only")," use GRPC/Protobuf\ninstalled from your system (e.g. in your ",(0,a.kt)("inlineCode",{parentName:"p"},"apt")," repository)."),(0,a.kt)("p",null,"If you have a custom version of GRPC installed in ",(0,a.kt)("inlineCode",{parentName:"p"},"/usr/local"),",\nwe recommend deleting it, by removing files in:"),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("inlineCode",{parentName:"li"},"/usr/local/bin")," (e.g. ",(0,a.kt)("inlineCode",{parentName:"li"},"grpc-cpp-plugin"),")"),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("inlineCode",{parentName:"li"},"/usr/local/include")," (e.g. ",(0,a.kt)("inlineCode",{parentName:"li"},"grpc++/"),")"),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("inlineCode",{parentName:"li"},"/usr/local/lib")," (e.g. ",(0,a.kt)("inlineCode",{parentName:"li"},"libgrpc++.so"),")"),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("inlineCode",{parentName:"li"},"/usr/local/lib/pkgconfig")," (e.g. ",(0,a.kt)("inlineCode",{parentName:"li"},"grpc++.pc"),")")),(0,a.kt)("p",null,"You can also compile GRPC and Protobuf from source,\nby setting ",(0,a.kt)("inlineCode",{parentName:"p"},"DBUILD_GRPC_LIB=ON")," when running ",(0,a.kt)("inlineCode",{parentName:"p"},"cmake"),".\nHowever, GRPC is difficult to cross-compile, which is why we recommend\nusing the pre-compiled system version from ",(0,a.kt)("inlineCode",{parentName:"p"},"apt"),"."),(0,a.kt)("h2",{id:"predictable-names-for-wifi-interfaces"},'"Predictable names" for WiFi interfaces'),(0,a.kt)("p",null,(0,a.kt)("a",{parentName:"p",href:"https://wiki.debian.org/NetworkInterfaceNames#legacy"},"https://wiki.debian.org/NetworkInterfaceNames#legacy")),(0,a.kt)("p",null,"The scheme detailed above is the new standard default, but there's also a canonical way of overriding the default: you can use .link files to set up naming policies to suit your needs. Thus for instance if you have two PCs each of which has only a single wireless card, but one calls it wlp0s1 and the other wlp1s0, you can arrange for them both to use the name wifi0 to simplify sharing firewall configurations. For details see systemd.link(5)."),(0,a.kt)("p",null,'Here\'s a relatively futureproof "manual" version of the example given above:'),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre"}," #/etc/systemd/network/10-persistent-net.link\n [Match]\n MACAddress=01:23:45:67:89:ab\n\n [Link]\n Name=lan0\n")),(0,a.kt)("p",null,'Note: per systemd.link(5), you shouldn\'t use a name that the kernel might use for another interface (for example "eth0").'),(0,a.kt)("p",null,"It is also possible to reorganize the naming policy by overriding /lib/systemd/network/99-default.link, for instance to insist that all network interfaces are named purely by MAC address:"),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre"}," #/etc/systemd/network/99-default.link\n [Match]\n OriginalName=*\n\n [Link]\n NamePolicy=mac\n MACAddressPolicy=persistent\n")),(0,a.kt)("p",null,"The folder ",(0,a.kt)("inlineCode",{parentName:"p"},"./scripts")," contains the ",(0,a.kt)("inlineCode",{parentName:"p"},"predictable_wifi_name.sh")," script to automaticall create the above lik file."),(0,a.kt)("p",null,"Usage:"),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre",className:"language-console"},"sudo ./scripts/predictable_wifi_name.sh source_if_name destination_fi_name\n")),(0,a.kt)("h2",{id:"stop-wpa_supplicant-listenning-on-wifi-interfaces-raspberry-pi-case"},"Stop wpa_supplicant listenning on WiFi interfaces (Raspberry Pi case)"),(0,a.kt)("p",null,"Disable the entire wap_supplicant add the below line to ",(0,a.kt)("inlineCode",{parentName:"p"},"/etc/dhcpcd.conf"),":"),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre"},"nohook wpa_supplicant\n")),(0,a.kt)("p",null,"Disable only for a particular wifi interface ",(0,a.kt)("inlineCode",{parentName:"p"},"wlanx")," add the below line to ",(0,a.kt)("inlineCode",{parentName:"p"},"/etc/dhcpcd.conf"),":"),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre"},"denyinterfaces wlanx\n")),(0,a.kt)("h2",{id:"libmicrohttp-tls"},"libmicrohttp TLS"),(0,a.kt)("p",null,"If ",(0,a.kt)("inlineCode",{parentName:"p"},"libgnutls")," and ",(0,a.kt)("inlineCode",{parentName:"p"},"libcrypt")," are not installed, ",(0,a.kt)("inlineCode",{parentName:"p"},"libmicrohttp")," cannot compile\nTLS support, and ",(0,a.kt)("inlineCode",{parentName:"p"},"restsrv")," will fail to start."),(0,a.kt)("p",null,"Because of this, make sure you have the following installed:\n(there should now be an error if they are not installed)"),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre",className:"language-bash"},"sudo apt-get install libgnutls-dev libgnutls28-dev\n")))}d.isMDXComponent=!0}}]);