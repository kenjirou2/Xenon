#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char buffer[1024];

    WSAStartup(MAKEWORD(2, 2), &wsa);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(2000);

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Connection failed\n");
        return 1;
    }

    printf("Connected\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));

        int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);

        if (bytes > 0) {
            printf("%s\n", buffer);
        }
        else if (bytes == 0) {
            printf("Server closed connection\n");
            break;
        }
        else {
            // optional: avoid CPU spam
            Sleep(100);
        }
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}