#ifndef VERSION_H
#define VERSION_H

#if defined (__linux__) || defined (__APPLE__) || defined (__unix__) || defined (__FreeBSD__) || defined (__OpenBSD__) || defined (__NetBSD__)
    #define INVALID_SOCKET (-1)
#endif

#include "../../../Include/protohttp/protohttp.h"

const char* version(void);
int update(void);

#endif
