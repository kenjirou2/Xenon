#include "misc/menu.h"

addrctx CTX;
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

            else if (strcmp(arg[i], "-v") == 0 || strcmp(arg[i], "-version") == 0)
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
                char type[16] = NULL;
                char family[16] = NULL;

                for (int x = i + 1; x < argc; x++)
                {

                    if (strcmp(arg[x], "-p") == 0)
                    {

                        if (x + 1 >= argc) return -1;

                        port = atoi(arg[x + 1]);
                        xenon_init(&CTX, ANYADDR, port);

                        x++;

                    }

                    else if (strcmp(arg[x], "-TCP") == 0 || strcmp(arg[x], "-UDP") == 0 || strcmp(arg[x], "-TLS") == 0)
                    {
                        strcpy(type, arg[x]);
                    }

                    else if (strcmp(arg[x], "-ipv4") == 0 || strcmp(arg[x], "-ipv6") == 0)
                    {
                        strcpy(family, arg[x]);
                    }

                    else
                    {
                        break;
                    }

                }
                
                if (port < 0 || type[0] == '\0' || family[0] == '\0')
                {
                    fprintf(stderr, RED"\nmissing or invalid arguments for -conn\n"BLACK);
                    return -1;
                }

                SOCKET sock = xenon_socket(type, family);
                if (sock == INVALID_SOCKET)
                {
                    fprintf(stderr, RED"\nfailed to create socket\n"BLACK);
                    return -1;
                }

                xenon_BL(sock);
                __pexec(sock);

                return 0;

            }

            else if (strcmp(arg[i], "-sconn") == 0 || strcmp(arg[i], "-specconn") == 0)
            {

                int port = -1;
                char type[16] = NULL;
                char family[16] = NULL;
                char* IP = NULL;

                for (int x = 1; x < argc; x++)
                {

                    if (strcmp(arg[x], "-p") == 0)
                    {
                        if (x + 1 >= argc) return -1;

                        port = atoi(arg[x + 1]);
                        xenon_init(&CTX, ANYADDR, port);
                        x++;
                    }

                    else if (strcmp(arg[x], "-TCP") == 0 || strcmp(arg[x], "-UDP") == 0 || strcmp(arg[x], "-TLS") == 0)
                    {
                        strcpy(type, arg[x]);
                    }

                    else if (strcmp(arg[x], "-ipv4") == 0 || strcmp(arg[x], "-ipv6") == 0)
                    {
                        strcpy(family, arg[x]);
                    }

                    else if (sscanf(arg[x], "-a %12s", IP) == 12 || sscanf(arg[x], "-addr %12s", IP)
                    {
                        
                    }

                    else
                    {
                        break;
                    }

                }

            }

            else { return Exit; }

        }

    }   

    return 0;

}