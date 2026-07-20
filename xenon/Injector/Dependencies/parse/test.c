#include "parse.h"

int main()
{
	
	char* src = GetSource("C:\\Windows\\System32\\kernel32.dll");
	if (src == NULL)
	{
		printf("\nfailed to get source");
		return -1;
	}
	
	DWORD fp = GetDynamicFunctionAddress(src, "OpenProcess");
	if (!fp || fp == -1)
	{
		fprintf(stderr, "failed to get function rva");
		return -1;
	}
	
	printf("function address : %p", fp);
	
	return 0;
	
}