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
        login();
        menu();
        __init();
    }

    else if (argc > 1)
    {
        
        for (int i = 1; i < argc; i++)
        {

            if (strcmp(arg[i], "-h") == 0 || strcmp(arg[i], "-help") == 0 || strcmp(arg[i], "?") == 0) {help_menu();}

            else if (strcmp(arg[i], "-v") == 0)
            {
                printf(WHITE"\n%s"BLACK, version());
            }
            else if (strcmp(arg[i], "-v?") == 0 || strcmp(arg[i], "-v ?") == 0)
            {
                printf(WHITE"\n%s"BLACK, httparse(version()).status_text);
			}

            else if (strcmp(arg[i], "-init") == 0)
            {
                WSAres = WININIT(WSAres);
            }

            else if (strcmp(arg[i], "-conn") == 0 || strcmp(arg[i], "-randconn") == 0)
            {

                int port = -1;
                char type[16] = {0};
                char family[16] = {0};

                for (int j = i+1; j < 4; j++)
                {

                    if (strncmp(arg[j], "-p", 2) == 0)
                    {

                        port = atoi(arg[i + 1]);
                        printf("%d", port);
                        xenon_init(&CTX, ANYADDR, port);

                        if (strlen(arg[i+1]) == 4)
                        {
                            strcpy(type, arg[i]);
                            printf("\n%s", type);
                        }

                        if (strlen(arg[i+1]) == 4)
                        {
                            strcpy(family, arg[i]);
                            printf("\n%s", family);
                        }
                    }
                    else
                    {
                        printf("\ninvalid argument for [random-connection]");
                        return -1;
                    }

                    j++;

                }

                printf("\n");
                system("\npause");

                if (port == -1 || type[0] == '\0' || family[0] == '\0')
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
                fprintf(stderr, WHITE"\ninvalid argument: %s"BLACK, arg[i]);
				return -1;
            }
        }

    }   

    return 0;

}