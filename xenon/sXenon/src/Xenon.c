#include "misc/menu.h"

addrctx CTX;
struct sockaddr* sockinfo;
int WSAres = -1;

int main(int argc, char* arg[10])
{

    (void)arg;
    (void)argc;

    if (argc == 1)
    {
        menu();
        __init();
    }

    else if (argc > 1)
    {

        for (int i = 1; i < argc; i++)
        {

            if (strcmp(arg[i], "-h") == 0 ||
                strcmp(arg[i], "-help") == 0 ||
                strcmp(arg[i], "?") == 0) {help_menu();}

            else if (strcmp(arg[i], "-v") == 0)
            {
                printf(WHITE"\n%s"BLACK, version());
            }

            else if (strcmp(arg[i], "-init") == 0)
            {
                WSAres = WININIT(WSAres);
            }

            else if (strcmp(arg[i], "-conn") == 0 || strcmp(arg[i], "-randconn") == 0)
            {

                int port = -1;
                char type[16] = { 0 };
                char family[16] = { 0 };

                for (int j = 1; j < argc; j++)
                {
                    if (strncmp(arg[j], "-p", 2) == 0)
                    {
						port = atoi(arg[j] + 2);
                        xenon_init(&CTX, ANYADDR, port);
                    }

                    if (strcmp(arg[j], "-TCP") == 0 || strcmp(arg[j], "-UDP") == 0 || strcmp(arg[j], "-TLS") == 0)
                    {
						type = arg[j];
                    }

                    if (strncmp(arg[j], "-ipv", 4) == 0)
                    {
						family = arg[j];
                    }
                }

                if (port == -1 || type[0] == NULL || family[0] == NULL)
                {
                    fprintf(stderr, "\nmissing arguments for -conn\n");
                    return -1;
                }

                SOCKET sock = xenon_socket(type, family);

                if (sock == INVALID_SOCKET)
                {
                    fprintf(stderr, "\nfailed to create socket\n");
                    return -1;
                }

                xenon_BL(sock, sockinfo);
                __pexec(sock);

                return 0;
            }

            else if (strcmp(arg[i], "-sconn") == 0 || strcmp(arg[i], "-specconn") == 0)
            {
                return 0;
            }

            else if (strcmp(arg[i], "-mconn") == 0 || strcmp(arg[i], "-multiconn") == 0)
            {
                return 0;
            }

            else
            {
                fprintf(stderr, "\ninvalid argument: %s", arg[i]);
				return -1;
            }
        }

    }   

    return 0;

}