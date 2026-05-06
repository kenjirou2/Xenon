#ifndef memory
#define memory

#include <tlhelp32.h>
#include "windows.h"

typdef struct
{

	DWORD pid;
	DWORD64 base_address;

} process_info;


#endif