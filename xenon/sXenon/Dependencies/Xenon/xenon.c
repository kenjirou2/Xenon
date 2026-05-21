#include <stdio.h>
#include <string.h>
#include "xenon.h"
#include "../../../Include/driver/windows.h"

extern struct addrctx CTX;
extern struct sockaddr_in sockCTX_in;
extern struct sockaddr* sockCTX;



int WININIT(void)
{

	WSADATA wsaData;

	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		fprintf(stderr, "\nWSAStartup failed: %d\n", iResult);
		return 1;
	}

	return 0;

}


int xenon_init(addrctx* CTX, char* dstaddr[16], int dstport)
{

	CTX.dstport = dstport;
	CTX.dstaddr = dstaddr;

	sockCTX.sin_family = AF_INET;
	socCTX.sin_port = htons(CTX.dstport);
	socCTX.sin_addr.s_addr = inet_addr(CTX.dstaddr);

	return 0;

}

int xenon_socket()
{

	SOCKET Sock = socket(2, 1, 6);
	if (Sock == INVALID_SOCKET)
	{
		fprintf(stderr, "\n[-] Socket creation failed with error: %d\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	return 0;
}

int xenon_BLA(SOCKET Socket, struct sockaddr* psockaddr)
{

	int BindRes = bind(Socket, psockaddr, sizeof(sockCTX_in));
	if (BindRes == SOCKET_ERROR)
	{
		fprintf(stderr, "\n[-] Bind failed with error: %d\n", WSAGetLastError());
		closesocket(Socket);
		WSACleanup();
		return -1;
	}

	int ListenRes = listen(Socket, 5);
	if (ListenRes == SOCKET_ERROR)
	{
		fprintf(stderr, "\n[-] Listen failed with error: %d\n", WSAGetLastError());
		closesocket(Socket); 
		WSACleanup();
		return -1;
	}

	Socket = accept(Socket, NULL, NULL);
	if (Socket == INVALID_SOCKET)
	{
		fprintf(stderr, "\n[-] Accept failed with error: %d\n", WSAGetLastError());
		closesocket(Socket);
		WSACleanup();
		return -1;
	}


	return 0;
}