#ifndef XENONHlp_H
#define XENONHlp_H


#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>


typedef struct {
    char ip[INET_ADDRSTRLEN];
    char host[256];
} CLIENT;

int GetClient()
{

    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == INVALID_SOCKET) return 1;

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(890);

    bind(server, (struct sockaddr*)&addr, sizeof(addr));
    listen(server, SOMAXCONN);

    printf("Server listening...\n");

    while (1) {

        struct sockaddr_in clientAddr;
        int len = sizeof(clientAddr);

        SOCKET client = accept(server, (struct sockaddr*)&clientAddr, &len);

        if (client == INVALID_SOCKET)
            continue;

        CLIENT c;

        inet_ntop(AF_INET, &clientAddr.sin_addr, c.ip, sizeof(c.ip));

        printf("Client connected: %s:%d\n",
               c.ip,
               ntohs(clientAddr.sin_port));

        closesocket(client);
    }

    closesocket(server);
    WSACleanup();
	
	getchar();
	
    return 0;
}

#endif