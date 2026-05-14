#ifndef XENON_H
#define XENON_H

#define XENON_VERSION "1.2.5"
#define INVALID_SOCK 0xFFFFFFFF


typedef struct
{

	char ip[16];
    int PORT;

} addrctx;


#if defined(_WIN32) || defined(_WIN64)

#include <winsock.h>
int WININIT(void);
        
#elif defined(__linux__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__) || defined(__APPLE__)

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#else

#error "\a\nUnsupported Operating system"

#endif


int xenon_init();
int xenon_socket();
int xenon_BLA();
int __pexec();


#endif