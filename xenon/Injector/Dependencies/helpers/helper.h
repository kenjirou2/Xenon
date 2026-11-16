#ifndef helpers_h
#define helpers_h

#include <stdio.h>
#include "../../../Include/driver/windows.h"
#include "../../../Include/driver/memory.h"


int GetPID(const char* Pname);
HANDLE GetHandle(int PID);

#endif