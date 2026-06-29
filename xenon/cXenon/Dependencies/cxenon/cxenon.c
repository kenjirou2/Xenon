#include "cxenon.h"

int WININIT(void)
{

#if defined(_WIN32)

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		fprintf(stderr, "\n\afailed to initilize ws2_32.dll");
		return Exit;
	}

	return 0;

#else
	return 0;

#endif
	return UNKNOWN;
	
}


ClientCTX CliInit(pClientCTX CTX)
{

}

SOCKET client_socket(SOCKET Socket)
{

	Socket = socket(AF_INET, SOCK_STREAM, 0);
	if(Socket == INVALID_SOCKET)
	{
		fprintf(stderr, "\nfailed to create a socket");
		return -1;
	}
	
	return Socket

}

int client_conn(SOCKET Socket)
{

	if(connect(Socket, ))

}