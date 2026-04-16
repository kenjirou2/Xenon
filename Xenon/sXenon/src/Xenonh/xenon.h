#ifndef XENON_H
#define XENON_H


#include <stdio.h>
#include <stdint.h>
#include "Dependencies/driver/socket.h"
#include "Dependencies/driver/windows.h"
#include "Dependencies/IP/ip.h"
#include "Dependencies/string.h"

#define KILOBYTE 1024
char host[NI_MAXHOST];

typedef struct{

	char *IP[16];
	char *cPORT[2];
	uint16_t PORT;
	
} XENON_CTX;

extern XENON_CTX CTX;



int WSAINIT();
int Xterminal();
SOCKET Soc(const char* PORT, struct addrinfo** passed);
int Socstp(SOCKET Socket, struct addrinfo** passed);
SOCKET ConACC(SOCKET Socket, struct sockaddr_in* CLIaddr);
int GetCLIname(struct sockaddr_in* socaddr);
int cmd(SOCKET CLISocket);



#endif