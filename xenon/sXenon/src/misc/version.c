#include "version.h"

int version(void)
{

	struct addrinfo* reslt;
	const char request[1024];
	char wrequest[1024];
	size_t written = 0;

	OpenSSLIntilize();
	SSL_CTX* CTX = SSLCTX();
	if (!CTX) { return 1; }

	REQUEST type = Httpbuild("GET");
	HttpbuildRequest(type, "github.com", wrequest, sizeof(request));

	SOCKET Socket = HttpOpenBridge("github.com", "443", &reslt);
	if (Socket == INVALID_SOCKET) { return 1; }
	if (HttpConnect(Socket, reslt) != 0) { return 1; }

	SSL* sslo = WrapSocketTLS(CTX, Socket, "github.com");
	if (!sslo) { return 1; }

	HttpsendSSL(sslo, request, &written);

	HttprecvFullSSL(sslo);

	CloseTLS(sslo, CTX, Socket);

	return 0;

}

int update(void)
{
	return 0;
}
