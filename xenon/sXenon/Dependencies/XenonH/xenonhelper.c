#include "xenonhelper.h"

extern addrctx CTX;
extern int WSAres;
static int count = 0;

CLIENT clients[NCLIENTSMAX];

int GetHostName(const struct sockaddr *SA, int sizeofSA_in, char* host)
{
    return getnameinfo(SA, sizeofSA_in, host, NI_MAXHOST, NULL, 0, NI_NAMEREQD);
}

int GetClient(int WSAres)
{

    if (WSAres != 0)
    {
        fprintf(stderr, RED"\nWSA not inizilized, %d"BLACK, WSAres);
        return -1;
    }

    SOCKET Socket = socket(AF_INET, SOCK_STREAM,0);
    if (Socket == INVALID_SOCKET)
    { 
        fprintf(stderr, "\nfailed to create socket for getclient %d", XenonGetLastError());
        return -1; 
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(CTX.dstport);

    bind(Socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    listen(Socket, SOMAXCONN);
    printf(PURPLE"\n\rLooking for connections on port ["CYAN"%d"PURPLE"]"BLACK, CTX.dstport);

    while (1)
    {

        struct sockaddr_in ClientAddr = { 0 };
        int len = sizeof(ClientAddr);

        SOCKET clientSock = accept(Socket, (struct sockaddr*)&ClientAddr, &len);


        if (clientSock == INVALID_SOCKET)
        {
            fprintf(stderr, RED"\nfailed to accept connection %d"BLACK, XenonGetLastError());
        }

        if (count >= NCLIENTSMAX)
        {
            printf(PURPLE"\a\nMAX amount of connections reached, Closing socket"BLACK);
            closesocket(clientSock);
            return -1;
        }

        clients[count].Socket = clientSock;
        strcpy(clients[count].IP, inet_ntoa(ClientAddr.sin_addr));
        
        if(GetHostName((struct sockaddr*)&ClientAddr, sizeof(ClientAddr), clients[count].HOST) != 0)
        {
            fprintf(stderr, "\nfailed to get host name %d", XenonGetLastError());
            return -1;
        }

        count++;

        printf(GREEN"\n\n\n================== CLIENTS ==================\n"BLACK);
        printf(GREEN"\nID               IP          HOST"BLACK);

        for (int i = 0; i < count; i++)
        {
            printf(GREEN"\r\n[%d]       [%s]        [%s]"BLACK, i, clients[i].IP, clients[i].HOST);
        }

    }

    return count;

}


int GetId(char* argid, size_t size)
{

    int id = atoi(argid);

    if (id < 0 || id > NCLIENTSMAX)
    {
        fprintf(stderr, RED"\ninvalid client ID"BLACK);
        return -1;
    }
	if (id > (int)(size))
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

DWORD WINAPI ThreadGetClient(void* arg)
{

    int WSAres = (*(int*)arg);
    if (!GetClient(WSAres))
    {
        fprintf(stderr, "\n\afailed to call threaded gc");
    }

    return 0;

}