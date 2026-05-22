#ifndef XENONHlp_H
#define XENONHlp_H

#define NCLIENTSMAX 100

typedef struct {

    char IP[16];
    char HOST[255];
    SOCKET Socket;

} CLIENT;

int GetClient(void);

#endif