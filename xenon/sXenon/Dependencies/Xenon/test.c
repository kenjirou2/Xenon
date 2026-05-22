#include <stdio.h>
#include <string.h>
#include "xenon.h"
#include "xenonhelper.h"

addrctx CTX;

int main()
{

	char *addr = LOCAL;
	int PORT = 5555;

	WININIT();
	xenon_init(&CTX, addr, PORT);
	GetClient();
	SOCKET Sock = xenon_socket();
	xenon_BL(Sock, (struct sockaddr*)&sockCTX_in);

	char c = getchar();
	if(c == ' '){ return 1 ;}

	return 0;

}
