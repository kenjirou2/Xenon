#include "version.h"

const char* version(void)
{

	struct addrinfo* reslt;
	const char request[1024];
	char wrequest[1024];
	size_t written = 0;

	OpenSSLIntilize();
	SSL_CTX* CTX = SSLCTX();
	if (!CTX) { return NULL; }

	//REQUEST type = Httpbuild("GET");
	HttpbuildRequest("GET", "github.com", wrequest, sizeof(wrequest));

	SOCKET Socket = HttpOpenBridge("github.com", "443", &reslt);
	if (Socket == INVALID_SOCKET) { return NULL; }
	if (HttpConnect(Socket, reslt) != 0) { return NULL; }

	SSL* sslo = WrapSocketTLS(CTX, Socket, "github.com");
	if (!sslo) { return NULL; }

	HttpsendSSL(sslo, wrequest, &written);
	char* response = HttprecvFullSSL(sslo);

	CloseTLS(sslo, CTX, Socket);

	return response;

}

int update(void)
{
	return 0;
}
