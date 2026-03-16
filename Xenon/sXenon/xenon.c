#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "Dependencies/driver/windows.h"
#include "Dependencies/driver/socket.h"
#include "Dependencies/driver/memory.h"
#include "Dependencies/IP/ip.h"
#include "Dependencies/protohttp/protohttp.h"


#define KILOBYTE 1024

int Socinfo();
char *Socket();
int RnSD(SOCKET socket);


int main()
{

	uint16_t *PORT = 0;
	char ipaddr[32] = 0;
	char ipv4cmpres;

	while (PORT == 0 && ipaddr == 0)
	{
		printf("PORT> ");
		scanf("%hu", &PORT);
		printf("IP> ");
		scanf("%d", &ipaddr);
	}

	ipv4cmpres = ipv4cmp(ipaddr);
	printf("%s", ipv4cmp);
	Socinfo();

	return 0;

}

int Socinfo()
{

	struct addrinfo *gres = NULL;
	struct addrinfo *ptr = NULL;
	struct addrinfo socinfo = NULL;

	ZeroMemory(&socinfo, sizeof(socinfo));

	socinfo.ai_family = AF_INET;
	socinfo.ai_socktype = SOCK_STREAM;
	socinfo.ai_protocol = IPPROTO_TCP;
	socinfo.ai_flags = AI_PASSIVE;

	getaddri = getaddrinfo(NULL, &PORT, &socinfo, &gres);
	if (getaddri != 0) {
		printf("[-] Failed to retrive socket info");
		return 1;
	}

	if (socket())
	{
		printf("\n%s",socket);
	}


	return 0;


}

char *Socket()
{

	struct sockaddr_in server;

	uint64_t Soc = INVALID_SOCKET;
	uint64_t WSAAPI ACSoc = INVALID_SOCKET;

	int BIND = NULL;
	int LISTEN = NULL;


	server.sin_family = AF_INET;
	server.sin_addr.s_addr = ipaddr;
	server.sin_port = htons(PORT);

	Soc = socket(AF_INET, SOCK_STREAM, 0);
	if (Soc == NULL)
	{
		printf("[-] Failed to create socket");
		WSACleanup();
		return 1;
	}

	BIND = bind(Soc, (struct sockaddr_in)&server, sizeof(server));
	if (BIND == NULL)
	{
		printf("[-]:::ERROR::In Func::socket:::");
		freeaddrinfo(BIND);
		closesocket(Soc);
		WSACleanup();
		return "Socket failed to bind";
	}

	LISTEN = listen(Soc, 5);
	if (LISTEN == NULL)
	{
		printf("[-]:::ERROR::In Func::socket:::");
		closesocket(Soc);
		WSACleanup();
		return "Socket failed to listen";
	}

	ACSoc = accept(Soc, NULL, NULL);
	if (ACSoc == NULL)
	{
		printf("[-]:::ERROR::In Func::socket:::");
		WSACleanup();
		closesocket(Soc);
		return "Socket failed to recive connection";
	}

	RnSD(Soc);

}

int RnSD(SOCKET socket)
{

	const char recvBuff[KILOBYTE];
	const char sendBuff[KILOBYTE];

	int recvresult = NULL;
	int sendresult = NULL;

	recvresult = recv(socket, recvBuff, sizeof(recvBuff), 0);
	if (recvresult == 1)
	{
		printf();

	}



	
}


void Versionget()
{

	


}
