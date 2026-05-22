#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{

	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
		fprintf(stderr, "WSAStartup failed: %d\n", iResult);
        return 1;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == INVALID_SOCKET)
    {
        printf("Socket failed\n");
        return 1;
    }

    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(5555);

    // connect to local server
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Connecting...\n");

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("Connection failed\n");
        return 1;
    }

    printf("Connected to server!\n");

    // keep alive loop
    char msg[] = "%s hello from client";

	send(sock, msg, sizeof(msg), 0);

    closesocket(sock);
    WSACleanup();

    return 0;
}