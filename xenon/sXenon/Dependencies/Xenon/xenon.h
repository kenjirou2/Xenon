#ifndef XENON_H
#define XENON_H

#define LOCAL "127.0.0.1"
#define ANYADDR "0.0.0.0"

#include "../../../Include/ansiiC/AnsiiC.h"


extern struct sockaddr_in sockCTX_in;


typedef struct
{

	char *dstaddr;
    int dstport;

} addrctx, *paddrctx;


#if defined(_WIN32) || defined(_WIN64)
	
	#include "../../../Include/driver/socket.h"
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
int xenon_BL(SOCKET Socket, struct sockaddr* paddrinfo);
int __pexec(void);
int XENON(void);

#endif