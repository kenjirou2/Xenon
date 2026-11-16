#ifndef PARSER_H
#define PARSER_H

#if defined(_WIN32)

#define REBASE(prefbase, realbase, offset)((void*)(realbase - prefbase) + offset))
#define WINSOCKDLL "C:/Windows/System32/ws2_32.dll"
#define KERNEL32DLL "C:/Windows/System32/kernel32.dll"
#include "../helpers/helper.h"


typedef enum
{
	Error							= (int)0x0A,
	INVALID_DOS_SIGNATURE			= (int)0x01,
	INVALID_NT_SIGNATURE			= (int)0x02,
	INVALID_NT_OFFSET				= (int)0x03,
	ALLOCATION_FAILURE				= (int)0x04,
	PARSE_INFO_EMPTY				= (int)0x05,
	HEADER_COPY_FAILED				= (int)0x06,
	SECTION_COPY_FAILED				= (int)0x07,
	LOADED_PARSED_DATA_HEADERS		= (int)0x08,
	REBASE_FAILED					= (int)0x09,
	MANUAL_MAP_PARSE_OK				= (int)0x0B,
	DYNAMIC_FUNCTION_LOAD_FAILED	= (int)0x0C,
	INVALID_PROCESSOR_ARCH			= (int)0x0D,
	INVALID_EXECUTABLE_IMAGE		= (int)0x0E,
	ALLOCATION_RIGHTS_FAILURE		= (int)0x0F,
    INVALID_POINTER                 = (int)0x10,
    SEEK_FAIL                       = (int)0x11,
    FILE_OPEN_FAIL                  = (int)0x12,
    FILE_SIZE                       = (int)0x13,
	OK								= (int)0x00,
	Exit							= (int)0x99
} errcode;

typedef struct
{
	errcode result;
	IMAGE_OPTIONAL_HEADER* OptionalHeaderAddress;
	IMAGE_NT_HEADERS* NTHeader;
	DWORD sizeofimage;
	WORD numberofsections;
	DWORD sizeofheaders;
	int sizeofoptionalheader;
	HMODULE newimagebase;
	void* oldimagebase;
	int PID;
	HANDLE pHandle;
	const char* pname;
} ParseInfo;


char* GetSource(const char* Fname);
int GetFileSizeEX(const char* Fname);
ParseInfo* ManualMapPEHeader(const char* src, const char* pname);
int WriteHeaders(char* src, ParseInfo* info);
int BaseRelocate(ParseInfo* info);
//--    int UnloadDll(void);
DWORD DynamicFunctionLoad(const char* dll, const char* function);


#else
#error "parse.h is invalid for this kernel."

#endif

#endif