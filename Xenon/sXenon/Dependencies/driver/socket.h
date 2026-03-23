#ifdef _WIN32

  #include <winsock2.h>
  #include <ws2tcpip.h>

#elseif _LINUX_

  #include <sys/socket.h>

#endif
