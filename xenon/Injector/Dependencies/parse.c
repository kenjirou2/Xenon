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

	char* buff = nullptr;

	int fsize = GetFileSize("example.txt");
	if (fsize == 0)
	{
		fprintf(stderr, "\nfailed to get file size.");
		return ERROR;
	}

	FILE* openf = fopen(Fname, "rb");
	if (openf == NULL)
	{
		fprintf(stderr, "\nerror: GetSource-> failed to open file.");
		return ERROR;
	}

	buff = malloc(sizeof(fsize));
	int readf = fread(buff, 1, sizeof(fsize), openf);
	if (readf < sizeof(fsize))
	{
		fprintf(stderr, "\nerror: GetSource-> failed to read file.");
		free(buff);
		return ERROR;
	}

	status = OK;

	return status;

}

int ParsePEHeader(char* src, ParseInfo* info)
{

	status = ERROR;

	IMAGE_NT_HEADERS*		INTHeader		= nullptr;
	IMAGE_OPTIONAL_HEADER*	IOptionalHeader	= nullptr;
	IMAGE_FILE_HEADER*		IFileHeader		= nullptr;

	info = malloc(sizeof(ParseInfo));
	if (info == NULL)
	{
		fprintf(stderr, "\nerror: parseDOSHeader-> failed to allocate memory.")
	}

	if ((IMAGE_DOS_HEADER*)src->e_magic != 0x4D5A)
	{
		fprintf(stderr, "\n\afile is not an portable executable.");
		return ERROR;
	}

	info->NToffset = (IMAGE_DOS_HEADER*)src->e_lfanew;

	INTHeader = (IMAGE_NT_HEADERS*)(src + info->NToffset);
	IOptinalHeader = (IMAGE_OPTIONAL_HEADER*)(INTHeader->IOptinalHeader);
	IFileHeader = (IMAGE_FILE_HEADER*)(INTHeader->IFileHeader);



}