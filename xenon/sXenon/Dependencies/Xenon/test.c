#include <stdio.h>
#include <string.h>
#include "xenon.h"

int main()
{

	addrctx CTX;
	char *addr = "192.168.1.42";

	WININIT();

	xenon_init(&CTX, addr, 80);
	SOCKET Sock = xenon_socket();
	xenon_BLA(Sock, (struct sockaddr*)&sockCTX_in);

	getchar();

	return 0;

}
