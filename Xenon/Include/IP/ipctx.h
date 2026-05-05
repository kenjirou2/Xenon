#ifndef IPCTX
#define IPCTX

#include <stdint.h>

typedef struct
{
	
	char* ip;
	int port;
	char* cport;
	
} IPCTX;

void portcast(int port, IPCTX ctx)
{
	ctx.cport;
	sprintf(ctx.cport, "%d", port);
	return;
}

#endif