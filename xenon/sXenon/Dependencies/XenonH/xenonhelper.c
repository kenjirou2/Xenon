#include "xenonhelper.h"

extern addrctx CTX;
extern int WSAres;
CLIENT clients[NCLIENTSMAX]; 
static int count = 0;


int GetClient(int WSAres)
{

    if (WSAres != 0)
    {
        fprintf(stderr, RED"\nWSA not inizilized, %d"BLACK, WSAres);
        return -1;
    }

    SOCKET Socket = socket(AF_INET, SOCK_STREAM,0);

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(CTX.dstport);

    bind(Socket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

    listen(Socket, SOMAXCONN);
    printf(PURPLE"\n\rLooking for connections on port ["BLUE"%d"PURPLE"]"BLACK, CTX.dstport);



    struct sockaddr_in ClientAddr;
    int len = sizeof(ClientAddr);

    SOCKET clientSock = accept(Socket, (SOCKADDR*)&ClientAddr, &len);

    if (clientSock == INVALID_SOCKET)
    {
        fprintf(stderr, RED"\nfailed to accept connection %d"BLACK, WSAGetLastError());
        return -1;
    }

    if (count >= NCLIENTSMAX)
    {
        printf(PURPLE"\a\nMAX amount of connections reached, Closing socket"BLACK);
        closesocket(clientSock);
        return -1;
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
    printf(GREEN"\nID   IP      HOST"BLACK);

    for (int i = 0; i < count; i++)
    {
        printf(GREEN"\r\n[%d]   [%s]    [%s]"BLACK, i, clients[i].IP, clients[i].HOST);
    }

    return count;

}

int GetId(char* argid, int size)
{

    int id = atoi(argid);

    if (id < 0 || id > NCLIENTSMAX)
    {
        fprintf(stderr, RED"\ninvalid client ID"BLACK);
        return -1;
    }
	if (id > size)
    {
        fprintf(stderr, RED"\ninvalid client ID"BLACK);
        return -1;
    }
	if (clients[id].Socket == INVALID_SOCKET)
    {
        fprintf(stderr, RED"\ninvalid client"BLACK);
        return -1;
    }

    printf(GREEN"\n[+] Client ["BLUE"%s"GREEN"] selected."BLACK, clients[id].HOST);

    return id;

}