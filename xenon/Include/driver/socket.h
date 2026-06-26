#ifndef network
#define network

#if defined(_WIN32)

#include <winsock2.h>
#include <ws2tcpip.h>

#elif defined(__linux__) || defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__) || defined(__APPLE__)

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>

typedef int SOCKET;

#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)

#else

#error Xenon library is incompatible with this kernel.

#endif