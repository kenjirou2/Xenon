#ifndef XENONHlp_H
#define XENONHlp_H

#define NCLIENTSMAX 100

#include "../Xenon/xenon.h"

typedef struct
{

    char IP[16];
    char HOST[255];
    SOCKET Socket;

} CLIENT;

int GetClient(int WSAres);
int GetId(char* argid, size_t size);

#endif