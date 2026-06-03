#include "xenonhelper.h"

extern addrctx CTX;
extern int WSAres;
CLIENT clients[NCLIENTSMAX]; 
static int count = 0;

SOCKET Sock(char* type, char* family)
{
	if (type == NULL || family == NULL)
    {
        fprintf(stderr, RED"\nInvalid socket type or family."BLACK);
        return INVALID_SOCKET;
    }
    if (strcmp(type, "TCP") == 0 || strcmp(type, "tcp") == 0)
    {
        if (strcmp(family, "IPv4") == 0 || strcmp(family, "ipv4") == 0)
        {
            return socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        }
        else if (strcmp(family, "IPv6") == 0 || strcmp(family, "ipv6") == 0)
        {
            return socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
        }
    }
    else if (strcmp(type, "UDP") == 0 || strcmp(type, "udp") == 0)
    {
        if (strcmp(family, "IPv4") == 0 || strcmp(family, "ipv4") == 0)
        {
            return socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        }
        else if (strcmp(family, "IPv6") == 0 || strcmp(family, "ipv6") == 0)
        {
            return socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
        }
    }
    else if (strcmp(type, "TLS") == 0 || strcmp(type, "tls") == 0)
    {
        fprintf(stderr, RED"\nTLS sockets are not supported in this version."BLACK);
        return INVALID_SOCKET;
	}

    return INVALID_SOCKET;

}

int GetClient(int WSAres, SOCKET Socket)
{

	if (WSAres != 0)
    {
        fprintf(stderr, RED"\nWSA not Inizilized, %d"BLACK, WSAres);
		return -1;
    }
    if (Socket == INVALID_SOCKET)
    {

    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(CTX.dstport);

    bind(Sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

    listen(Sock, SOMAXCONN);
    printf(PURPLE"\n\rLooking for connections on port ["BLUE"%d"PURPLE"]"BLACK, CTX.dstport);



    struct sockaddr_in ClientAddr;
    int len = sizeof(ClientAddr);

    SOCKET clientSock = accept(Sock, (SOCKADDR*)&ClientAddr, &len);

    if (clientSock == INVALID_SOCKET)


        if (count >= NCLIENTSMAX)
        {
            printf(PURPLE"\a\nMAX amount of connections reached, Closing socket"BLACK);
            closesocket(clientSock);
        }

    clients[count].Socket = clientSock;
    strcpy(clients[count].IP, inet_ntoa(ClientAddr.sin_addr));

    if (getnameinfo((SOCKADDR*)&ClientAddr, sizeof(ClientAddr),clients[count].HOST, sizeof(clients[count].HOST),NULL, 0, 0) != 0)
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

int Select(char* argid, int size)
{

    int id = atoi(argid);

    if (id < 0 || id > NCLIENTSMAX)
    {
        fprintf(stderr, RED"\nInvalid client ID."BLACK);
        return -1;
    }
	else if (id > size)
    {
        fprintf(stderr, RED"\nInvalid client ID."BLACK);
        return -1;
    }
	else if (clients[id].Socket == INVALID_SOCKET)
    {
        fprintf(stderr, RED"\nInvalid client."BLACK);
        return -1;
    }

    printf(GREEN"\n[+] Client ["BLUE"%s"GREEN"] selected."BLACK, clients[id].HOST);

    return id;

}