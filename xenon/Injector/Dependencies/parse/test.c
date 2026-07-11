#include "parse.h"

int main()
{
	
	char* src = GetSource("test.exe");
	if (src == NULL)
	{
		printf("\nfailed to get source");
		return -1;
	}
	
	DWORD fp = GetFunctionAddress(src, "OpenProcess");
	if (!fp)
	{
		fprintf(stderr, "failed to get function rva");
		return -1;
	}
	
	printf("function address : %p", fp);
	
	return 0;
	
}