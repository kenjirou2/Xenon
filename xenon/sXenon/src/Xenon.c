#include "misc/menu.h"

addrctx CTX;
int WSAres = -1;

int main(int argc, char* arg[5])
{

    (void)arg;
    (void)argc;

    menu();

    if (argc == 1)
    {
        __init();
    }
    else if (argc > 1)
    {

        for (int i = 1; i < argc; i++)
        {
            if (strcmp(arg[i], "-h") == 0)
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
            else if (strcmp(arg[i], "-v") == 0)
            {
                version();
            }
            else if (strcmp(arg[i], "-init") == 0)
            {
				WSAres = WININIT(WSAres);
            }
        }
    }
    return 0;
}