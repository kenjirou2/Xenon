#ifndef XENON_H
#define XENON_H

#define XENON_VERSION "0.1.0"
#define INVALID_SOCK 0xFFFFFFFF


typedef struct
{

	char* ip[16];
    int 

    
} addrctx;



#if defined(_WIN32) || defined(_WIN64)

    #include <winsock.h>

    int initWSAres = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (initWSAres != 0)
    {
        printf("WSAStartup failed: %d\n", initWSAres);
        return 1;
    }
        
#elif defined(__linux__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__) || defined(__APPLE__)

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>

#else

    #error "\a\nUnsupported Operating system"

#endif

#endif