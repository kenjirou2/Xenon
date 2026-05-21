#ifndef XENON_H
#define XENON_H

#define XENON_VERSION "1.3.2"

#include "../../../Include/ansiiC/AnsiiC.h"

extern struct sockaddr_in sockCTX_in;



typedef struct
{

	char *dstaddr;
    int dstport;

} addrctx, *paddrctx;


#if defined(_WIN32) || defined(_WIN64)

#include <winsock2.h>
#include <ws2tcpip.h>
#include "../../../Include/driver/windows.h"

int WININIT(void);
        
#elif defined(__linux__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__) || defined(__APPLE__)

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#else

#error "\a\nUnsupported Operating system"

#endif


int xenon_init(addrctx* CTX, char* addr, int port);
int xenon_socket(void);
int xenon_BLA(SOCKET Socket, struct sockaddr* psockaddr);
int __pexec(void);
int XENON(void);

#endif