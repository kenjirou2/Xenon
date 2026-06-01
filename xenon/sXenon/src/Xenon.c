#include "menu/menu.h"

addrctx CTX;
int WSAres = -1;

int main(int argc, char* arg[5])
{

    (void)arg;
    (void)argc;

    if (argc == 1)
    {
        __init();
    }
    if (argc > 5) { return -1; }
    else if (strcmp(arg[1], "-v") == 0)
    {
        printf("\nXenon v3.1.5");
    }
    else if (strcmp(arg[1], "-h") == 0)
    {
        printf("\nXenon v3.1.5");
        printf("\nUsage: Xenon [options] [arguments]\n");
        printf("\nSOCKET TYPES:");
        printf("\t\n -TCP : Transmission Control Protocol");
        printf("\t\n -UDP : User Datagram Protocol");
        printf("\t\n -TLS : Transport Layer Security");
        printf("\nOPTIONS:");
        printf("\t\n -v : Version");
        printf("\t\n -h/ -help / ? : Help");
        printf("\t\n -s : select [arguments]");
    }

    WININIT(WSAres);
    menu();

    return 0;
}