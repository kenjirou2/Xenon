#include "xenonhelper.h"
#include "xenon.h"
#include <stdio.h>

typedef struct {

    char IP[16];
    char HOST[255];
    SOCKET Socket;

} CLIENT;


extern addrctx CTX;

CLIENT clients[NCLIENTSMAX];

int GetClient(void)
{

    int count = 0;

    SOCKET Sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(5555);

    bind(Sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

    listen(Sock, SOMAXCONN);
    printf(PURPLE"\nLooking for connections on port ["BLUE"%d"PURPLE"]"BLACK, CTX.dstport);

    while (1)
    {

        struct sockaddr_in ClientAddr;
        int len = sizeof(ClientAddr);

        SOCKET clientSock = accept(Sock, (SOCKADDR*)&ClientAddr, &len);

        if (clientSock == INVALID_SOCKET)
            continue;

        if (count >= NCLIENTSMAX)
        {
            printf(PURPLE"\a\nMAX amount of connections reached, Closing socket"BLACK);
            closesocket(clientSock);
            continue;
        }

        clients[count].Socket = clientSock;
        strcpy(clients[count].IP, inet_ntoa(ClientAddr.sin_addr));

        if (getnameinfo((SOCKADDR*)&ClientAddr, sizeof(ClientAddr), clients[count].HOST, sizeof(clients[count].HOST), NULL, 0, 0) != 0)
        {
            fprintf(stderr, "\r\n[-] Failed to retrive host name%d", WSAGetLastError());
            return -1;
        }

        count++;

        printf(GREEN"\n\n\n================== CLIENTS ==================\n"BLACK);
        printf(GREEN"\nID ------------------ IP ___________________ HOST"BLACK);

        for (int i = 0; i < count; i++)
        {
            printf(GREEN"\r\n[%d] ------------------ [%s] ------------------ [%s]"BLACK, i, clients[i].IP, clients[i].HOST);
        }

    }

    closesocket(Sock);
    WSACleanup();

    return 0;

}

/*
int select(const char* ip)
{
    //recv(clients[0].Socket, NULL, 0, 0);
    __pexec();
    return 0;
}
*/