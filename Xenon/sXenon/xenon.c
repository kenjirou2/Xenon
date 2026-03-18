#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "Dependencies/driver/socket.h"
#include "Dependencies/driver/windows.h"
#include "Dependencies/IP/ip.h"

void WSAINIT();
int Xterminal();
SOCKET Soc(uint16_t PORT);
int Socstp(SOCKET socket, struct addrinfo* ret);

#define KILOBYTE 1024

int main()
{

	WSAINIT();
	uint16_t port = Xterminal();
	Soc(port);
	Socstp(socket, passed);

	return 0;

}


SOCKET Soc(uint16_t PORT)
{
	struct addrinfo** passed = NULL;
	SOCKET soc = INVALID_SOCKET;
	struct addrinfo* ptr = NULL;
	struct addrinfo socinfo;
	struct addrinfo* ret = &socinfo;

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

	soc = socket(ret->ai_family, ret->ai_socktype, ret->ai_protocol);
	if (soc == INVALID_SOCKET)
	{
		fprintf(stderr,"[-]::in func::socket::failed to create socket");
		return 1;
	}

	passed = &ret;
	return soc;

}

int Socstp(SOCKET socket, struct addrinfo* ret)
{


	int Bres = bind(socket, ret->ai_addr, (int)ret->ai_addrlen);
	if (Bres == SOCKET_ERROR)
	{
		fprintf(stderr, "[-]::in func::Socstp::failed to bind to %d", ret->ai_family);
		freeaddrinfo(ret);
		closesocket(socket);
		WSACleanup();
		return 1;
	}

	while (1)
	{

		if (listen(socket, 5) == SOCKET_ERROR)
		{
			int i = 1;
			fprintf(stderr, "[-]::in func::Socstp::failed to listen for connections Retrying[%d]", i);
			printf("\nPress Enter to stop");
			getchar();
			i++;
			continue;
		}

		return 0;

	}

	return 0;

}
/*
int ConACC()
{

	SOCKET clientaccSoc = INVALID_SOCKET;




}


int cmdsend()
{






}


int datarecv()
{

	


}

void VersionGET()
{

	

	
}


*/
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

void WSAINIT()
{

	WSADATA wsaData;
	if (WSAStrartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		fpritnf(stderr, "[-]::failed to initilize Winsock");
		return 1;
	}

	return;

}