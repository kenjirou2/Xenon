#include "xenon.h"

struct sockaddr_in sockCTX_in;
extern addrctx CTX;


int CloseSocket(SOCKET Socket)
{

#if defined(_WIN32)

    if (Socket == 0)
    {
	    closesocket(Socket);
    }
    else
    {
        closesocket(Socket);
        WSACleanup();
    }

#else
	close(Socket);

#endif
    return 0;
}

int XenonGetLastError(void)
{

	#if defined(_WIN32)
		return WSAGetLastError();
	#else
		return errno;

	#endif

}

int WININIT(int result)
{

#if defined(_WIN32)

	WSADATA wsaData;

	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		fprintf(stderr, RED"\nWSAStartup failed: %d\n"BLACK, result);
		return 1;
	}

	return result=0;;

#else
	return result=0;

#endif

	return 0;

}

addrctx* xenon_init(addrctx* CTX, char* addr, int port)
{

	if (addr == NULL)
	{ 
		CTX->dstaddr = LOCAL;
	}

	CTX->dstport = port;
	CTX->dstaddr = addr;

	sockCTX_in.sin_family = AF_INET;
	sockCTX_in.sin_port = htons(CTX->dstport);
	sockCTX_in.sin_addr.s_addr = inet_addr(LOCAL);


	return CTX;

}

SOCKET xenon_socket(const char* type, const char* family)
{ 

	if (strcmp(type, "-TCP") == 0)
	{
		if (strcmp(family, "-ipv4") == 0)
		{
			return socket(AF_INET, SOCK_STREAM, 0);
		}
		else if (strcmp(family, "-ipv6") == 0)
		{
			return socket(AF_INET6, SOCK_STREAM, 0);
		}
	}

	else if (strcmp(type, "-UDP") == 0)
	{
		if (strcmp(family, "-ipv4") == 0)
		{
			return socket(AF_INET, SOCK_DGRAM, 0);
		}
		else if (strcmp(family, "-ipv6") == 0)
		{
			return socket(AF_INET6, SOCK_DGRAM, 0);
		}
	}

	else if (strcmp(type, "-TLS") == 0)
	{
		if (strcmp(family, "-ipv4") == 0)
		{
			return socket(AF_INET, SOCK_STREAM, 0);
		}
		else if (strcmp(family, "-ipv6") == 0)
		{
			return socket(AF_INET6, SOCK_STREAM, 0);
		}
	}

	return INVALID_SOCKET;
	
}

int xenon_BL(SOCKET Socket)
{

	int BindRes = bind(Socket, (struct sockaddr*)&sockCTX_in, sizeof(sockCTX_in));
	if (BindRes == SOCKET_ERROR)
	{
		fprintf(stderr, RED"\n[-] Bind failed with error: %d\n"BLACK, XenonGetLastError());
        CloseSocket(Socket);
        return -1;
	}

	int ListenRes = listen(Socket, 5);
	if (ListenRes == SOCKET_ERROR)
	{
		fprintf(stderr, RED"\n[-] Listen failed with error: %d\n"BLACK, XenonGetLastError());
        CloseSocket(Socket);
		return -1;
	}
	
	printf(GREEN"\nListening"BLACK);

	SOCKET acc = accept(Socket, NULL, NULL);

	if (acc == INVALID_SOCKET)
	{
		fprintf(stderr, GREEN"\n[-] Accept failed with error: %d\n"BLACK, XenonGetLastError());
        CloseSocket(Socket);
		return -1;
	}

	return 0;

}

int xenon_bl_ex(SOCKET Socket, addrctx *CTX)
{

	struct sockaddr_in clientCTX_in = { 0 };
	int addrlen = sizeof(clientCTX_in);

	if (bind(Socket, (struct sockaddr*)&sockCTX_in, sizeof(sockCTX_in)) == SOCKET_ERROR)
	{
		fprintf(stderr, RED"\a\nfailed to bind : %d"BLACK, XenonGetLastError());
        CloseSocket(Socket);
		return -1;
	}

	if (listen(Socket, 5) == SOCKET_ERROR)
	{
		fprintf(stderr, RED"\a\nfailed to listen : %d"BLACK, XenonGetLastError());
        CloseSocket(Socket);
		return -1;
	}

	while (1)
	{

#if defined(_WIN32)
		SOCKET client = accept(Socket, (struct sockaddr*)&clientCTX_in, &addrlen);
#else
        SOCKET client = accept(Socket, (struct sockaddr*)&clientCTX_in, (socklen_t*)&addrlen);
#endif
		if (client == INVALID_SOCKET)
		{
			printf(RED"\nfailed to accept connection : %d"BLACK, XenonGetLastError());
			continue;
		}

		if (clientCTX_in.sin_addr.s_addr == inet_addr(CTX->dstaddr))
		{
			printf(GREEN"\n[+] Connected to [%s]"BLACK, CTX->dstaddr);
			return client;
		}

		CloseSocket(client);

	}

	return -1;

}
