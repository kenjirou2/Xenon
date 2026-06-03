#include "misc/menu.h"
#include "../../Include/IP/ip.h"

addrctx CTX;
struct sockaddr* psockinfo;
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
            if (strcmp(arg[i], "-h") == 0 || strcmp(arg[i], "-help") == 0 || strcmp(arg[i], "?") == 0)
            {
                printf(WHITE"\nXenon v3.1.5");
                printf("\nUsage: Xenon [options] [arguments]\n");
                printf("\nSOCKET TYPES:");
                printf("\t\n -TCP : Transmission Control Protocol");
                printf("\t\n -UDP : User Datagram Protocol");
                printf("\t\n -TLS : Transport Layer Security");
                printf("\nOPTIONS:");
                printf("\t\n -v : Version");
                printf("\t\n -h/ -help / ? : Help");
                printf("\t\n -s : select [arguments]"BLACK);
			}
            else if(strcmp(arg[i], "-v") == 0)
            {
                printf(WHITE"\n%s"BLACK, version());
            }
            else if(strcmp(arg[i], "-init") == 0)
            {
				WSAres = WININIT(WSAres);
            }
            else if (strcmp(arg[i], "-conn")==0 || strcmp(arg[i], "-randconn") == 0)
            {
				for (int port; int j = 0; j < argc; j++)
                {
                    if (sscanf(arg[j], "-p %d", &port) == 1)
                    {
                        xenon_init(&CTX, ANYADDR, port);
						for (char* type; int k = 0; k < argc; k++)
                        {
                            if (sscanf(arg[k], "-%s", type) == 1)
                            {
                                type = arg[k];
                                for (char* family; int l = 0; l < argc; l++)
                                {
                                    if (sscanf(arg[l], "-%5s", family) == 1)
                                    {
                                        xenon_BL(xenon_socket(type, family), psockinfo);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (strcmp(arg[i], "-sconn") == 0 || strcmp(arg[i], "-specconn") == 0)
            {
            }
            else if (strcmp(arg[i], "-mconn") == 0 || strcmp(arg[i], "-multiconn") == 0)
			{
            else{
				fprintf(stderr, "\ninvalid argument: %s", arg[i]);
                return -1;
            }
        }
    }   

    return 0;

}