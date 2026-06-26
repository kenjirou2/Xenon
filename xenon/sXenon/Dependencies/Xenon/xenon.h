#ifndef XENONh_H
#define XENONh_H

#define LOCAL "127.0.0.1"
#define ANYADDR "0.0.0.0"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include "../../../Include/ansiiC/AnsiiC.h"
#include "../../../Include/driver/socket.h"



typedef struct
{

	char *dstaddr;
    int dstport;

} addrctx, *paddrctx;



#if defined(__linux__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__) || defined(__APPLE__)

typedef int SOCKET;

#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)

#else

#error Xenon library is incompatible with this kernel.

#endif

int WININIT(int result);
int CloseSocket(SOCKET Socket);
addrctx* xenon_init(addrctx* CTX, char* addr, int port);
SOCKET xenon_socket(const char* type, const char* family);
int xenon_BL(SOCKET Socket);
int xenon_bl_ex(SOCKET Socket, addrctx* CTX);
int XenonGetLastError(void);

#endif
