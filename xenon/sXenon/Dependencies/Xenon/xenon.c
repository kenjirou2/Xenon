#include "xenon.h"

struct sockaddr_in sockCTX_in;
struct sockaddr* sockCTX;


int WININIT(int WSAres)
{

	WSADATA wsaData;

	WSAres = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (WSAres != 0)
	{
		fprintf(stderr, RED"\nWSAStartup failed: %d\n"BLACK, WSAres);
		return 1;
	}

	printf(GREEN"\n[+] Winsock initialized successfully."BLACK);

	return WSAres;

}

int xenon_init(addrctx* CTX, char* addr, int port)
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
			return socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		}
		else if (strcmp(family, "-ipv6") == 0)
		{
			return socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
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

	SOCKET acc = accept(Socket, NULL, NULL);
	if (acc == INVALID_SOCKET)
	{
		fprintf(stderr, "\n[-] Accept failed with error: %d\n", WSAGetLastError());
		closesocket(Socket); 
		WSACleanup();
		return -1;
	}

	return 0;

}