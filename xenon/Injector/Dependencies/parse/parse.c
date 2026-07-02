#include "parse.h"
#include "../helpers/helper.h"

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

	IMAGE_NT_HEADERS* INTHeader = nullptr;

	IMAGE_OPTIONAL_HEADER* IOptionalHeader = malloc(sizeof(IMAGE_OPTIONAL_HEADER));
	if (IOptinalHeader == NULL)
	{
		fprintf(stderr, "\n\afailed to allocate memory for IMAGE_OPTINAL_HEADER");
		return ERROR;
	}

	IMAGE_FILE_HEADER* IFileHeader = nullptr;

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
	IOptionalHeader = (IMAGE_OPTIONAL_HEADER)(INTHeader->IOptionalHeader);
	IFileHeader = (IMAGE_FILE_HEADER*)(INTHeader->IFileHeader);

	if (IOptionalHeader->Magic != 0x10b || IOptionalHeader != 0x20b)
	{
		fprintf(stderr, "\n\athis file is not an executable image.");
		free(info);
		return ERROR;
	}

	info->sizeofimage = IOptionalHeader->SizeOfImage;
	info->imagebase = IOptionalHeader->ImageBase;
	info->sizeofheaders = IOptionalHeader->SizeOfHeaders;

	status = OK;
	return status;

}

int BaseRelocate(ParseInfo* info)
{

	ProcessInfo procinfo = { 0 };
	status = ERROR;

	if (info == NULL)
	{
		fprintf(stderr, "\n\aptr->ptr failure");
		return status;
	}

	ParseInfo** pinfo = &info;
	IMAGE_DATA_DIRECTORY* Datadirectory[16] = nullptr;
	IMAGE_DIRECTORY_ENTRY_BASERELOC* BaseReloc = nullptr;
	int rvaBaseReloc = -1;
	int sizeBaseReloc = -1;

	Datadirectory = IOptionalHeader->Datadirectory[16];
	if (Datadirectory->Size == 0 || Datadirectory->VirtualAddress == 0)
	{
		fprintf(stderr, "\n\afailed to retrive DataDirectory");
		free(info);
		return ERROR;
	}

	rvaBaseReloc = Datadirectory[5]->VirtualAddress;
	if (rvaBaseReloc == -1)
	{
		fprintf(stderr, "\n\afailed to retrive RVA of Base Relocation Table.");
		free(info);
		return ERROR;
	}

	sizeBaseReloc = Datadirectory[5]->Size;
	if (sizeBaseReloc == -1)
	{
		fprintf(stderr, "\n\afailed to retrive Size of Base Relocation Table.");
		free(info);
		return ERROR;
	}

	procinfo.pname = "example.exe";
	procinfo.PID = GetPID(procinfo.pname)
	procinfo.pHandle = GetHandle(procinfo.PID);

	*(info)->mBase = VirtualAllocEx(procinfo.pHandle, NULL, (*pinfo)->sizeofimage, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE) == NULL);
	if (*(info)->mHandle == NULL)
	{
		fprintf(stderr, "\n\afailed to allocate memory for target DLL.");
		free(info);
		return ERROR;
	}

	int oldprotect;
	if (VirtualProtectEx(procinfo.pHandle, *(info)->mBase, PAGE_EXECUTE_READWRITE, &oldprotect) == 0)
	{
		fprintf(stderr, "\n\afailed to change protection on memory section.");
		free(info);
		return ERROR;
	}

}