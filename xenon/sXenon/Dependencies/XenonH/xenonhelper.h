#ifndef XENONHlp_H
#define XENONHlp_H

#define NCLIENTSMAX 100

#include <winsock2.h>

typedef struct {

    char IP[16];
    char HOST[255];
    SOCKET Socket;

} CLIENT;

int GetClient(void);
int Select(char* argid);

#endif