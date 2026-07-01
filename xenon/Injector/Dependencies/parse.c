#include "parse.h"

errcode status;

int GetFileSize(const char* Fname)
{

	char buff[1024];
	int readf;
	int fsize;

	FILE* openf = fopen(Fname, "rb");
	if (openf == NULL)
	{
		fprintf("\nerror: GetFileSize-> failed to open file.")
	}

	while ((readf = fread(buff, 1, sizeof(buff), openf) > 0)
	{
		fsize += readf;
	}

	return fsize;

}

char* GetSource(const char* Fname)
{

	status = ERROR;

	int fsize = GetFileSize("example.txt");
	if (fsize == 0)
	{
		fprintf(stderr, "\nfailed to get file size.");
		return ERROR;
	}



}