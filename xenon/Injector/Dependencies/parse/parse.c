#include "parse.h"


int GetFileSizeEX(const char* Fname)
{

	FILE* file = fopen(Fname, "rb");
	if (file == NULL)
	{
		fprintf(stderr, "\n\aGetFileSizeEX-> failed to open file.");
		return -1;
	}

	if (fseek(file, 0, SEEK_END) != 0)
	{
		fprintf(stderr, "\n\aGetFileSizeEX-> failed to seek file.");
		fclose(file);
		return -1;
	}

	long size = ftell(file);

	if (size < 0)
	{
		fprintf(stderr, "\n\aGetFileSizeEX-> failed to get file size.");
		fclose(file);
		return -1;
	}

	fclose(file);

	return (int)size;
}

char* GetSource(const char* Fname)
{

	char* buff = NULL;

	int fsize = GetFileSizeEX(Fname);
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
		return NULL;
	}

	fclose(openf);
	return buff;

}



ParseInfo* ManualMapPEHeader(const char* src, const char* pname)
{

	errcode status = Error;


	IMAGE_DOS_HEADER*		dos		= (IMAGE_DOS_HEADER*)(src);
	IMAGE_NT_HEADERS*		INTHeader		= NULL;
	IMAGE_OPTIONAL_HEADER*	IOptionalHeader = NULL;
	IMAGE_FILE_HEADER*		IFileHeader		= NULL;


	ParseInfo* info = malloc(sizeof(ParseInfo));
	if (info == NULL)
	{
		fprintf(stderr, "\nerror: parseDOSHeader-> failed to allocate memory.");
		return NULL;
	}

	if (dos->e_magic != IMAGE_DOS_SIGNATURE)
	{
		fprintf(stderr, "\n\afile is not an portable executable.");
		info->result = INVALID_DOS_SIGNATURE;
		return info;
	}

	INTHeader		= (IMAGE_NT_HEADERS*)(src + dos->e_lfanew);
	info->NTHeader 	= INTHeader;
	IOptionalHeader = &INTHeader->OptionalHeader;
	IFileHeader		= &INTHeader->FileHeader;

	info->OptionalHeaderAddress = IOptionalHeader;

#if defined(_WIN64) || defined(_WIN32)
	if (IFileHeader->Machine != IMAGE_FILE_MACHINE_AMD64 && IFileHeader->Machine != IMAGE_FILE_MACHINE_I386)
	{
		fprintf(stderr, "\n\athis executable is not compatible with x86-64 and x86-32");
		info->result = INVALID_PROCESSOR_ARCH;
		return info;
	}
#endif

	info->numberofsections = (WORD)(IFileHeader->NumberOfSections);
	info->sizeofoptionalheader = (int)(IFileHeader->SizeOfOptionalHeader);

	if (IOptionalHeader->Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC && IOptionalHeader->Magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC)
	{
		fprintf(stderr, "\n\athis file is not an executable image.");
		info->result = INVALID_EXECUTABLE_IMAGE;
		return info;
	}

	info->pname = pname;
	info->sizeofheaders = (DWORD)(IOptionalHeader->SizeOfHeaders);
	info->sizeofimage	= (DWORD)(IOptionalHeader->SizeOfImage);
	info->oldimagebase = &IOptionalHeader->ImageBase;
	info->PID = GetPID(info->pname);
	info->pHandle = GetHandle(info->PID);
	info->newimagebase  = VirtualAllocEx(info->pHandle, NULL, (DWORD)(info->sizeofimage), MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	if (info->newimagebase == NULL)
	{
		fprintf(stderr, "\n\afailed to allocate memory in target process.");
		info->result = ALLOCATION_FAILURE;
		return info;
	}

	DWORD oldprotect;
	if (VirtualProtectEx(info->pHandle, info->newimagebase, info->sizeofimage, PAGE_EXECUTE_READWRITE, &oldprotect) == 0)
	{
		fprintf(stderr, "\n\afailed to change protection rights on allocated memory space.");
		VirtualFreeEx(info->pHandle, info->oldimagebase, 0, MEM_RELEASE);
		info->result = ALLOCATION_RIGHTS_FAILURE;
		return info;
	}


	status = MANUAL_MAP_PARSE_OK;
	info->result = status;
	return info;

}

int WriteHeaders(char* src, ParseInfo* info)
{

	errcode status = Error;

	if (info->result != MANUAL_MAP_PARSE_OK)
	{
		fprintf(stderr, "\n\aParseInfo error: %d", info->result);
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
		free(info);
		status = HEADER_COPY_FAILED;
		return status;
	}

	IMAGE_SECTION_HEADER* pSectionHeader = IMAGE_FIRST_SECTION(info->NTHeader);

	for (int i = 0; i > info->numberofsections; i++)
	{

		if (WriteProcessMemory(info->pHandle, (void*)(info->oldimagebase + pSectionHeader[i].VirtualAddress), (void*)(info->oldimagebase + pSectionHeader[i].PointerToRawData), pSectionHeader[i].SizeOfRawData, NULL) == 0)
		{
			fprintf(stderr, "\n\afailed to write section headers to target process.");
			free(info);
			status = SECTION_COPY_FAILED;
			return status;
		}

	}

	status = LOADED_PARSED_DATA_HEADERS;
	info->result = status;
	return status;

}


DWORD DynamicFunctionLoad(const char* dll, const char* function);
{
    
    if (*dll == '\0' || *name == '\0') { return -2; }
    IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)src;

    if (dos->e_magic != IMAGE_DOS_SIGNATURE) { return -1; }
    
    IMAGE_NT_HEADERS* nt = (IMAGE_NT_HEADERS*)(src + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE){ return -1; }

    
    IMAGE_EXPORT_DIRECTORY* exports = (IMAGE_EXPORT_DIRECTORY*)(src + nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
    DWORD* names = (DWORD*)(src + exports->AddressOfNames);
    DWORD* functions = (DWORD*)(src + exports->AddressOfFunctions);
    WORD* ordinals = (WORD*)(src + exports->AddressOfNameOrdinals);

    for (int i = 0; i < exports->NumberOfNames; i++)
    {
        char* name = (char*)(src + names[i]);

        if (strcmp(name, function) == 0)
        {
            WORD oridinal = ordinals[i];
            return functions[oridinal];
        }
    }
    
    return -1;
    
}