#ifndef ipv
#define ipv

#include <stdio.h>
#include <stdint.h>
#include <string.h>

int ipv4cmp(const char *ip)
{

	if (!ip) { return 1; }

	unsigned int d1, d2, d3, d4;

	if (sscanf(ip, "%d.%d.%d.%d+", &d1, &d2, &d3, &d4) != 4)
	{
		return 0;
	}

	return 1;

}




#endif