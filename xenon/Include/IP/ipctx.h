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
	snprintf(ctx.cport, "%d", port);
	return;
}

#endif
