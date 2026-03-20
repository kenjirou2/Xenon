#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "Dependencies/driver/socket.h"
#include "Dependencies/driver/windows.h"
#include "Dependencies/IP/ip.h"
#include "Dependencies/string.h"


int WSAINIT();
int Xterminal();
SOCKET Soc(const char *PORT, struct addrinfo** passed);
int Socstp(SOCKET Socket, struct addrinfo** passed);
SOCKET ConACC(SOCKET Socket, struct sockaddr_in* CLIaddr);
int GetCLIname(struct sockaddr_in* socaddr);
int cmd(SOCKET CLISocket);


#define KILOBYTE 1024
char host[NI_MAXHOST];


int main()
{

	WSAINIT();

	struct sockaddr_in CLIaddr;
	struct addrinfo* res = NULL;
	struct addrinfo** passed = &res;

	char strport[6];
	uint16_t port;
	SOCKET soc;

	port = Xterminal();
	intconv(port, strport);
	soc = Soc(strport, passed);
	Socstp(soc, passed);

	ConACC(soc, &CLIaddr);

	return 0;

}


SOCKET Soc(const char *PORT, struct addrinfo** passed)
{

	SOCKET Soc = INVALID_SOCKET;

	struct addrinfo* ret = NULL;
	struct addrinfo socinfo;

	SecureZeroMemory(&socinfo, sizeof(socinfo));

	socinfo.ai_family = AF_INET;
	socinfo.ai_socktype = SOCK_STREAM;
	socinfo.ai_protocol = IPPROTO_TCP;
	socinfo.ai_flags = AI_PASSIVE;

	if (getaddrinfo(NULL, PORT, &socinfo, &ret) != 0)
	{
		fprintf(stderr,"[-]::in func::socket::failed to return addrinfo");
		return 1;
	}

	Soc = socket(ret->ai_family, ret->ai_socktype, ret->ai_protocol);
	if (Soc == INVALID_SOCKET)
	{
		fprintf(stderr,"[-]::in func::socket::failed to create socket");
		return 1;
	}

	*passed = ret;
	return Soc;

}

int Socstp(SOCKET soc, struct addrinfo** passed)
{


	int Bres = bind(soc, (*passed)->ai_addr, (int)(*passed)->ai_addrlen);
	if (Bres == SOCKET_ERROR)
	{
		fprintf(stderr, "[-]::in func::Socstp::failed to bind to %d", (*passed)->ai_family);
		freeaddrinfo((*passed));
		closesocket(soc);
		WSACleanup();
		return 1;
	}

	printf("\n[+]::in func::Socstp::Successfully bound socket");

	while (1)
	{

		if (listen(soc, 5) == SOCKET_ERROR)
		{
			int i = 1;
			fprintf(stderr, "\n[-]::in func::Socstp::failed to listen for connections Retrying[%d]", i);
			printf("\nPress Enter to stop");
			getchar();
			i++;
			continue;
		}

		printf("\n[+]::in func::Socstp::Listening");

		return 0;

	}

	return 0;

}

SOCKET ConACC(SOCKET Socket, struct sockaddr_in* CLIaddr)
{

	SOCKET clientaccSoc = INVALID_SOCKET;
	int addrlen = sizeof(struct sockaddr_in);

	clientaccSoc = accept(Socket, (struct sockaddr*)CLIaddr, &addrlen);
	if (clientaccSoc == INVALID_SOCKET)
	{

		printf("\n[-]::in func::ConACC::failed to accept incoming connection");
		closesocket(Socket);
		WSACleanup();

		return INVALID_SOCKET;

	}

	printf("\n[+]::in func::ConACC::Successfully connected\r");


	return clientaccSoc;


}


int cmd(SOCKET CLISocket)
{

	struct sockaddr_in CLIaddr;
	if (GetCLIname(&CLIaddr) != 0) { return 1; }

	char buff[KILOBYTE];
	int recvres;
	int sendres;
	int bufflen = KILOBYTE;

	do
	{

		recvres = recv(CLISocket, buff, bufflen, 0);
		if (recvres > 0)
		{
			printf("\nrecv data : [ %d ]", recvres);
		}

		printf("[%s]>" , host);
		scanf("%s", buff);

		sendres = send(CLISocket, buff, bufflen, 0);




	} while (1);

	return 0;

}


int Xterminal()
{

	uint16_t PORT = 0;
	char IP[5];


	while (PORT == 0)
	{
		printf("PORT> ");
		scanf("%hu", &PORT);

		printf("IP> ");
		scanf("%4s", IP);
	}

	if (ipv4cmp(IP) != 0)
	{
		perror("Invalid IP address");
	}


	return PORT;

}

int WSAINIT()
{

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		fprintf(stderr, "[-]::failed to initilize Winsock");
		return 1;
	}

	return 0;

}

int GetCLIname(struct sockaddr_in* socaddr)
{

	char service[NI_MAXSERV];

	int gni = getnameinfo(
		(struct sockaddr*)socaddr,
		sizeof(struct sockaddr_in),
		host,
		sizeof(host),
		service,
		sizeof(service),
		NI_NUMERICHOST | NI_NUMERICSERV
	);

	if (gni != 0) { return 1; }

	return 0;

}