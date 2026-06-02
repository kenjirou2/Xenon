#ifndef VERSION_H
#define VERSION_H

#include "../../../Include/protohttp/protohttp.h"

int version(void)
{

	struct addrinfo* reslt;
	char request[1024];

	OpenSSLIntilize();
	SSL_CTX* CTX = SSLCTX();
	if (!CTX) { return 1; }

	REQUEST type = Httpbuild("GET");
	HttpbuildRequest("GET", "github.com", request, sizeof(request));

	SOCKET Socket = HttpOpenBridge("github.com", "443", &reslt);
	if (Socket == INVALID_SOCKET) { return 1; }
	if (HttpConnect(Socket, reslt) != 0) { return 1; }

	SSL* sslo = WrapSocketTLS(CTX, Socket, "github.com");
	if (!sslo) { return 1; }

	HttpsendSSL(sslo, request, strlen(request));

	HttprecvFullSSL(sslo);

	CloseTLS(sslo, CTX, Socket);

	return 0;

}

int update(void)
{

}

#endif