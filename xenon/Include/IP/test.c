#include <stdio.h>
#include "ip.h"

int main()
{

	char IP = "192.168.1.2";
	int inip = ipint(IP);
	if (ipcmp(inip) != 0)
	{
		printf("IP size is not correct.\n");
		return -1;
	}

	return 0;
}