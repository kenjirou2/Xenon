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

                for (int j = i + 1; j < argc; j++)
                {

                    if (strcmp(arg[j], "-p") == 0)
                    {

                        if (j + 1 >= argc) return -1;

                        port = atoi(arg[j + 1]);
                        xenon_init(&CTX, ANYADDR, port);

                        j++;

                    }

                    else if (strcmp(arg[j], "-TCP") == 0 || strcmp(arg[j], "-UDP") == 0 || strcmp(arg[j], "-TLS") == 0)
                    {
                        strcpy(type, arg[j]);
                    }

                    else if (strcmp(arg[j], "-ipv4") == 0 || strcmp(arg[j], "-ipv6") == 0)
                    {
                        strcpy(family, arg[j]);
                    }

                    else
                    {
                        break;
                    }

                }

                if (port < 0 || type[0] == '\0' || family[0] == '\0')
                {
                    fprintf(stderr, "\nmissing or invalid arguments for -conn\n");
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