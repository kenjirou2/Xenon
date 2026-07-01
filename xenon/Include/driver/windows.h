#ifndef NTapi
#define NTapi

#if defined(_WIN32)

#include <windows.h>

#else

#error "windows.h cannot be used in this kernel."

#endif
#endif
