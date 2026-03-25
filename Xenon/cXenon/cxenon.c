#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "Dependencies/driver/socket.h"
#include "Dependencies/driver/windows.h"
#include "Dependencies/IP/ip.h"
#include "Dependencies/string.h"

#define PORT "27022"
#define Port 27022
#define ip "192.168.1.25"


SOCKET Soc();
SOCKET Con(SOCKET Sock);

int main()
{


}

SOCKET Soc()
{

	SOCKET SOC = INVALID_SOCKET;

	struct addrinfo* ret = NULL;
	struct addrinfo socinfo;

	SecureZeroMemory(&socinfo, sizeof(socinfo));

	socinfo.ai_family = AF_INET;
	socinfo.ai_socktype = SOCK_STREAM;
	socinfo.ai_protocol = IPPROTO_TCP;

	int res = getaddrinfo(ip, PORT, &socinfo, &ret);
	if (ret != 0)
	{
		fprintf(stderr, "\n[-]::in func::Soc::failed getaddrinfo()::");
		WSACleanup();
		return 1;
	}

	SOC = socket(ret->ai-family, ret->ai_socktype, ret->ai_protocol);
	if (SOC == INVALID_SOCKET)
	{
		fprintf(stderr, "\n[-]::in func::failed to create socket object::");
		freeeaddrinfo(ret);
		WSACleanup();
		return 1;
	}

	return SOC;


}


SOCKET Con(SOCKET Sock)
{




}