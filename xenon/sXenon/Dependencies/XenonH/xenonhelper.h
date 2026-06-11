#ifndef XENONHlp_H
#define XENONHlp_H

#define NCLIENTSMAX 100

#include "../Xenon/xenon.h"

typedef struct {

    char IP[16];
    char HOST[255];
    SOCKET Socket;

} CLIENT;

int MultiClient(int WSAres);
int GetClient(int WSAres, char* addr);
int GetId(char* argid, size_t size);

#endif