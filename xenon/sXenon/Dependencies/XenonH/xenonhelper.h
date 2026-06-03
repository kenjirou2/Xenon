#ifndef XENONHlp_H
#define XENONHlp_H

#define NCLIENTSMAX 100

#include "../Xenon/xenon.h"

typedef struct {

    char IP[16];
    char HOST[255];
    SOCKET Socket;

} CLIENT;

int GetClient(int ires);
int GetId(char* argid, int size);

#endif