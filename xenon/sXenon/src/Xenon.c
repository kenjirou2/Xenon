#include "misc/menu.h"
#include <time.h>


addrctx CTX;
int WSAres = -1;

int main(int argc, char* arg[])
{

#if defined(_WIN32)
    WSAres = WININIT(WSAres);
#endif
     
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
                char type[16] = { 0 };
                char family[16] = { 0 };

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

            }

            else if (strcmp(arg[i], "-sconn") == 0 || strcmp(arg[i], "-singleconn") == 0)
            {

                int port = -1;
                char type[16] = { 0 };
                char family[16] = { 0 };
                char* IP = { 0 };

                for (int x = i+1; x < argc; x++)
                {

                    if (strcmp(arg[x], "-p") == 0)
                    {
                        if (x + 1 >= argc) return -1;

                        port = atoi(arg[x + 1]);
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

                    else if (strcmp(arg[x], "-a") == 0 || strcmp(arg[x], "-addr") == 0)
                    {
                        if (x + 1 >= argc) { return -1; }
                        IP = arg[++x];
                    }

                    else
                    {
                        printf("\ninvalid or missing commands.");
                        return Exit;
                    }

                }

                if (port == -1 && IP == NULL && type[0] == '\0' && family[0] == '\0')
                {
                    printf("\ninvalid or missing commands.");
                    return Exit;
                }

                xenon_init(&CTX, IP, port);
                __pexec(xenon_bl_ex(xenon_socket(type, family), &CTX));

            }

            else if (strcmp(arg[i], "-mconn") == 0 || strcmp(arg[i], "-multiconn") == 0)
            {

                int port = -1;

                for (int x = i+1; x < argc; x++)
                {

                    if (strcmp(arg[x], "-p") == 0)
                    {
                        if (x + 1 >= argc) { return -1; }

                        port = atoi(arg[x+1]);
                    }
                    if (port > -1)
                    {
                        xenon_init(&CTX, NULL, port);
                        GetClient(WSAres);
                    }
                    else
                    {
                        printf("\ninvalid or missing commands.");
                        return Exit;
                    }
                
                }

            }

            else { return Exit; }

        }

    }   

    return 0;

}





