#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;

    // Init Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        WSACleanup();
        return 1;
    }

    // Server setup
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(2000);

	while (1)
	{
		// Connect only
		if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
			printf("Connection failed\n");
		}
		else {
			printf("Connected successfully\n");
		}
	}
	
    // Cleanup
    closesocket(sock);
    WSACleanup();

    return 0;
}