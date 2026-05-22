#include <stdio.h>
#include "../Dependencies/Xenon/xenon.h"
#include "../Dependencies/Xenon/xenonhelper.h"

int main()
{

	addrctx CTX;

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