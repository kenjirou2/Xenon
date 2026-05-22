#include <stdio.h>
#include <string.h>
#include "xenon.h"

struct sockaddr_in sockCTX_in;
struct sockaddr* sockCTX;


int WININIT(void)
{

	WSADATA wsaData;

	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		fprintf(stderr, RED"\nWSAStartup failed: %d\n"BLACK, iResult);
		return 1;
	}

	printf(GREEN"\n[+] Winsock initialized successfully."BLACK);

	return 0;

}


int xenon_init(addrctx *CTX, char* addr, int port)
{
	
	if (addr == NULL)
    {
        fprintf(stderr, RED"\n[-] ERROR: addr->NULL"BLACK);
        return -1;
    }
	
	if (strcmp(addr, LOCAL) != 0 && strcmp(addr, ANYADDR) != 0)
	{
		fprintf(stderr, RED"\a\n[-] ERROR: Address Option Not Found"BLACK);
		return -1;
	}

	CTX->dstport = port;
	CTX->dstaddr = addr;

	sockCTX_in.sin_family = AF_INET;
	sockCTX_in.sin_port = htons(CTX->dstport);
	sockCTX_in.sin_addr.s_addr = inet_addr(CTX->dstaddr);

	return 0;

}

int xenon_socket()
{
	
	printf(GREEN"\n[+] xenon_init successfully completed."BLACK);
	SOCKET Socket = socket(2, 1, 6);
	if (Socket == INVALID_SOCKET)
	{
		fprintf(stderr, RED"\n[-] Socket creation failed with error: %d\n"BLACK, WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf(GREEN"\n[+] Socket created successfully."BLACK);

	return Socket;
	
}

int xenon_BL(SOCKET Socket, struct sockaddr* psockaddr)
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


	return 0;
}

int __pexec()
{
	return 0;
}
