#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP   "127.0.0.1"
#define SERVER_PORT 5555

int main()
{
    WSADATA wsa;
    SOCKET sock;

    struct sockaddr_in server;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock == INVALID_SOCKET)
    {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Configure server address
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to server
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Connect failed: %d\n", WSAGetLastError());

        closesocket(sock);
        WSACleanup();

        return 1;
    }

    printf("[+] Connected to server\n");

    // Send data
    char msg[] = "hello from client";

    send(sock, msg, sizeof(msg), 0);

    // Cleanup
    closesocket(sock);
    WSACleanup();

    getchar();

    return 0;
}