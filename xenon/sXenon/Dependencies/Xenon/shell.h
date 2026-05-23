#include <stdio.h>
#include "xenon.h"
#include "../XenonH/xenonhelper.h"

int __pexec()
{

	char buff[1024];
	char sarg[17];

	while (1)
	{

		printf(">> ");
		scanf("%s", buff);

		if (strcmp(buff, "-init") == 0)
		{
			WININIT();
		}
		else if (strcmp(buff, "-gc") == 0)
		{
			GetClient();
		}
		else if (strcmp(buff, "exit") == 0)
		{
			break;
			return 0;
		}
		else if (sscanf(buff, "-select %17s", sarg) == 1)
		{
			select(sarg);
		}
		else
		{

			if(send(clients[0].Socket, buff, strlen(buff), 0) < 0)
			{
				fprintf(stderr, RED,"\nerror: %d\n",BLACK, WSAGetLastError());
			}

			continue;

		}

	}

	return 0;

}