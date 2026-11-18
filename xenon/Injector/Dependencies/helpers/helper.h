#ifndef helpers_h
#define helpers_h

#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include "../parse/parse.h"
#include "../../../Include/driver/memory.h"

int GetPID(const char* Pname);
HANDLE GetHandle(uint32_t PID);

#endif