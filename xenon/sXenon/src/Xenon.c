#include "misc/menu.h"

addrctx CTX;
struct sockaddr* sockinfo;

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
            if (strcmp(arg[i], "-h") == 0 || strcmp(arg[i], "-help") == 0 || strcmp(arg[i], "?") == 0)
            {
				help_menu();
			}
            else if(strcmp(arg[i], "-v") == 0)
            {
                printf(WHITE"\n%s"BLACK, version());
            }
            else if(strcmp(arg[i], "-init") == 0)
            {
                int WSAres = -1;
				WSAres = WININIT(WSAres);
            }
            else if (strcmp(arg[i], "-conn")==0 || strcmp(arg[i], "-randconn") == 0)
            {

                int port;
                char* type = NULL;
                char* family = NULL;

				for (int j = 0; j < argc; j++)
                {
                    if (sscanf(arg[j], "-p %d", &port) == 1)
                    {
                        xenon_init(&CTX, ANYADDR, port);
						for (int k = 0; k < argc; k++)
                        {
                            if (sscanf(arg[k], "-%s", type) == 1)
                            {
                                type = arg[k];
                                for (int l = 0; l < argc; l++)
                                {
                                    if (sscanf(arg[l], "-%5s", family) == 1)
                                    {

										SOCKET sock = xenon_socket(type, family);
                                        if(sock == INVALID_SOCKET)
                                        {
                                            fprintf(stderr, "\n[-] Failed to establish connection.\n");
                                            return -1;
										}

										xenon_BL(sock, sockinfo);
                                        __pexec(sock);

                                        return 0;

                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (strcmp(arg[i], "-sconn") == 0 || strcmp(arg[i], "-specconn") == 0)
            {
                return 0;
            }
            else if (strcmp(arg[i], "-mconn") == 0 || strcmp(arg[i], "-multiconn") == 0)
            {
				return 0;
            }
            else{
				fprintf(stderr, "\ninvalid argument: %s", arg[i]);
                return -1;
            }
        }
    }   

    return 0;

}