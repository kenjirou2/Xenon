#include "parse.h"

int main()
{
	
	char* src = GetSource("test.exe");
	if (src == NULL)
	{
		printf("\nfailed to get source");
		return -1;
	}
	
	ParseInfo* info = ManualMapPEHeader(src, "test.exe");
	if (info == NULL)
	{
		printf("\nfailed to manually map");
		free(src);
		return -1;
	}
	
	free(info);
	
	return 0;
	
}