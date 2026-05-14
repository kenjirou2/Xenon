#include <stdio.h>
#include <string.h>
#include "xenon.h"
#include "../../../Include/driver/windows.h"

int WININIT(void)
{ 

	WSADATA wsaData;

	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("\nWSAStartup failed: %d\n", iResult);
		return 1;
	}

	return 0;

}

int xenon_init()
{



}