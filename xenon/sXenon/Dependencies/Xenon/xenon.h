#ifndef XENONh_H
#define XENONh_H

#define LOCAL "127.0.0.1"
#define ANYADDR "0.0.0.0"

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "../../../Include/ansiiC/AnsiiC.h"



typedef struct
{

	char *dstaddr;
    int dstport;

} addrctx, *paddrctx;




#if defined(_WIN32) || defined(_WIN64)
	
	#include "../../../Include/driver/socket.h"
	#include "../../../Include/driver/windows.h"

int WININIT(int WSAres);

SOCKET xenon_socket(const char* type, const char* family);
int xenon_BL(SOCKET Socket);
int xenon_bl_ex(SOCKET Socket, addrctx* CTX);


#elif defined(__linux__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__) || defined(__APPLE__)

	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>


#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)


    int xenon_socket(const char* type, const char* family);
    int xenon_BL(int Socket);
    int xenon_bl_ex(int Socket, addrctx* CTX);


#else

#error "\a\nUnsupported Operating system"


#endif

addrctx* xenon_init(addrctx* CTX, char* addr, int port);

#endif
