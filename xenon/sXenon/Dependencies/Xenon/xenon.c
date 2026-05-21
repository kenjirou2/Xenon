#include <stdio.h>
#include <string.h>
#include "xenon.h"
#include "../../../Include/driver/windows.h"


int WININIT(void)
{ 

	WSADATA wsaData;

	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("\nWSAStartup failed: %d\n", iResult);
		return 1;
	}

	return 0;

}


int xenon_init(addrctx *CTX, char *dstaddr[16], int dstport)
{

	CTX.dstport = dstport;
	CTX.dstaddr = dstaddr;

	sockCTX.sinfamily = AF_INET;
	socCTX.sinport = htons(CTX.dstport);
	socCTX.sinaddr.s_addr = inet_addr(CTX.dstaddr);

	return 0;

}

int xenon_socket()
{



	return 0;
}