#include <stdio.h>
#include <string.h>
#include "xenon.h"
#include "xenonhelper.h"

int main()
{

	addrctx CTX;
	char *addr = LOCAL;

	WININIT();
	GetClient();
	xenon_init(&CTX, addr, 890);
	SOCKET Sock = xenon_socket();
	xenon_BLA(Sock, (struct sockaddr*)&sockCTX_in);

	char c = getchar();
	if(c == ' '){ return 1 ;}

	return 0;

}
