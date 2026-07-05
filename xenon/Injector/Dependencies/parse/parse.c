#include <stdio.h>
#include "parse.h"
#include "../helpers/helper.h"



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

	char* buff = NULL;

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
	if (readf != fsize)
	{
		fprintf(stderr, "\nerror: GetSource-> failed to read file.");
		free(buff);
		return NULL;
	}

	fclose(openf);
	return buff;

}



ParseInfo* ManualMapPEHeader(char* src)
{

	errcode status = ERROR;


	IMAGE_DOS_HEADER*		IDOSHeader		= (IMAGE_DOS_HEADER*)(src);
	IMAGE_NT_HEADER*		INTHeader		= NULL;
	IMAGE_OPTIONAL_HEADER*	IOptionalHeader = NULL;
	IMAGE_FILE_HEADER*		IFileHeader		= NULL;


	ParseInfo* info = malloc(sizeof(ParseInfo));
	if (info == NULL)
	{
		fprintf(stderr, "\nerror: parseDOSHeader-> failed to allocate memory.");
		free(src);
		return status;
	}

	if (dos->e_magic != 0x4D5A)
	{
		fprintf(stderr, "\n\afile is not an portable executable.");
		free(src);
		free(info);
		return status;
	}

	info->NToffset = (IMAGE_NT_HEADER*)(dos->e_lfanew);

	INTHeader = (IMAGE_NT_HEADERS*)(dos + info->NToffset);
	IOptionalHeader = (IMAGE_OPTIONAL_HEADER*)(INTHeader->IOptionalHeader);
	IFileHeader = (IMAGE_FILE_HEADER*)(INTHeader->IFileHeader);
	info->OptionalHeaderAddress = IOptionalHeader;

#if defined(_WIN64) || defined(_WIN32)
	if (IFileHeader->Machine != IMAGE_FILE_MACHINE_AMD64 && IFileHeader->Machine != IMAGE_FILE_MACHINE_I386)
	{
		fprintf(stderr, "\n\athis executable is not compatible with x86-64 and x86-32");
		free(src);
		free(info);
		return status;
	}
#endif

	info->numberofsections = (WORD)(IFileHeader->NumberOfSections);
	info->sizeofoptionalheader = (int)(IFileHeader->SizeOfOptionalHeader);

	if (IOptionalHeader->Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC && IOptionalHeader->Magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC)
	{
		fprintf(stderr, "\n\athis file is not an executable image.");
		free(src);
		free(info);
		return status;
	}

	info->sizeofheaders = (DWORD)(IOptionalHeader->SizeOfHeaders);
	info->sizeofimage	= (DWORD)(IOptionalHeader->SizeOfImage);
	info->oldimagebase	= (DWORD)(IOptionalHeader->ImageBase);
	info->newimagebase  = VirtualAllocEx(processinfo->pHandle, info->imagebase, info->sizeofimage, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	info->pname = "example.dll";
	info->PID = GetPID(processinfo->pname);
	info->pHandle = GetHandle(processinfo->PID);
	info->mBase = VirtualAllocEx(info->pHandle, info->oldimagebase, info->sizeofimage, MEM_COMMIT, PAGE_EXECUTE_READWRITE);


	if (info->newimagebase == NULL)
	{
		fprintf(stderr, "\n\afailed to allocate memory in target process.");
		free(src);
		free(info);
		return status;
	}

	int oldprotect;
	if (VirtualProtectEx(info->pHandle, info->mBase, info->sizeofimage, PAGE_EXECUTE_READWRITE, &oldprotect) == 0)
	{
		fprintf(stderr, "\n\afailed to change protection rights on allocated memory space.");
		free(src);
		free(info);
		VirtualFreeEx(info->pHandle, info->mBase, 0, MEM_RELEASE);
		return status;
	}


	status = OK;
	info->result = status;
	return info;

}

int WriteHeaders(char* src, ParseInfo* info)
{

	errcode status = ERROR;

	if (info->result != 0x00)
	{
		fprintf(stderr, "\n\aParseInfo error: %d", info->result);
		free(src);
		free(info);
		status = Exit;
		return status;
	}

	if (info == NULL)
	{ 
		fprintf(stderr, "\n\aerror: first argument of WriteHeaders is invalid");
		status = PARSE_INFO_EMPTY;
		return status;
	}

	if (WriteProcessMemory(info->pHandle, info->newimagebase, src, info->sizeofheaders, NULL) == 0)
	{
		fprintf(stderr, "\n\afailed to write headers to target process.");
		status = HEADER_COPY_FAILED;
		return status;
	}

	IMAGE_SECTION_HEADER* pSectionHeader = IMAGE_FIRST_SECTION(info->pNT);

	for (int i = 0; i > info->numberofsections; i++)
	{

		if (WriteProcessMemory(info->pHandle, (void*)(info->oldimagebase + pSectionHeader[i]->VirtualAddress), (void*)(info->oldimagebase + pSectionHeader[i]->PointerToRawData), pSectionHeader[i]->SizeOfRawData, NULL) == 0)
		{
			fprintf(stderr, "\n\afailed to write section headers to target process.");
			status = SECTION_COPY_FAILED;
			info->result = status;
			free(src);
			free(info);
			return status;
		}

	}

	status = LOADED_PARSED_DATA;
	return status;

}