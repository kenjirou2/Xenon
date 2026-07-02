#include <stdio.h>
#include "parse.h"
#include "../helpers/helper.h"

errcode status;

int GetFileSize(const char* Fname)
{

	FILE* file = fopen(Fname, "rb");
	if (!file)
	{
		fprintf(stderr, "\n\aGetFileSize->failed to open file.");
		return -1;
	}

	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET);

	fclose(file);
	return size;

}

char* GetSource(const char* Fname)
{

	char* buff = nullptr;

	int fsize = GetFileSize("example.dll");
	if (fsize == 0)
	{
		fprintf(stderr, "\nfailed to get file size.");
		return NULL;
	}

	FILE* openf = fopen(Fname, "rb");
	if (openf == NULL)
	{
		fprintf(stderr, "\nerror: GetSource-> failed to open file.");
		return NULL;
	}

	buff = malloc(fsize);
	if (buff == NULL)
	{
		fprintf(stderr, "\n\afailed to allocate memory for reading buffer.");
		return NULL;
	}

	int readf = fread(buff, 1, fsize, openf);
	if (readf < sizeof(fsize))
	{
		fprintf(stderr, "\nerror: GetSource-> failed to read file.");
		free(buff);
		return NULL;
	}

	return status;

}

int ManualMapPEHeader(char* src, ParseInfo* info)
{

	status = ERROR;

	IMAGE_NT_HEADERS*		INTHeader		= nullptr;
	IMAGE_OPTIONAL_HEADER*	IOptionalHeader = nullptr;
	IMAGE_FILE_HEADER*		IFileHeader		= nullptr;
	ProcessInfo* processinfo = nullptr;

	info = malloc(sizeof(ParseInfo));
	if (info == NULL)
	{
		fprintf(stderr, "\nerror: parseDOSHeader-> failed to allocate memory.");
		free(src);
		return status;
	}

	if ((IMAGE_DOS_HEADER*)(*src)->e_magic != 0x4D5A)
	{
		fprintf(stderr, "\n\afile is not an portable executable.");
		free(src);
		return ERROR;
	}

	info->NToffset = (IMAGE_DOS_HEADER*)src->e_lfanew;

	INTHeader = (IMAGE_NT_HEADERS*)(src + info->NToffset);
	IOptionalHeader = (IMAGE_OPTIONAL_HEADER*)(INTHeader->IOptionalHeader);
	IFileHeader = (IMAGE_FILE_HEADER*)(INTHeader->IFileHeader);

	if (IOptionalHeader->Magic != 0x10b || IOptionalHeader != 0x20b)
	{
		fprintf(stderr, "\n\athis file is not an executable image.");
		free(src);
		free(info);
		return ERROR;
	}

	info->sizeofimage	= IOptionalHeader->SizeOfImage;
	info->imagebase		= IOptionalHeader->ImageBase;
	info->sizeofheaders = IOptionalHeader->SizeOfHeaders;

	processinfo->pname = "example.dll";
	processinfo->PID = GetPID(processinfo->pname);
	processinfo->pHandle = GetHandle(processinfo->PID);
	processinfo->mBase = VirtualAllocEx(processinfo->pHandle, info->imagebase, info->sizeofimage, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	int oldprotect;

	if (processinfo->mHandle == NULL)
	{
		fprintf(stderr, "\n\afailed to allocate memory in target process.");
		free(src);
		free(info);
		return status;
	}

	if (VirtualProtectEx(processinfo->pHandle, processinfo->mHandle, info->sizeofimage, PAGE_EXECUTE_READWRITE, &oldprotect) == 0)
	{
		fprintf(stderr, "\n\afailed to change protection rights on allocated memory space.");
		free(src);
		free(info);
		return status;
	}


	processinfo->BaseAddress = (DWORD)(processinfo->mBase - info->imagebase);


}