#ifndef PARSER_H
#define PARSER_H


#if defined(_WIN32)

#define REBASE(x, y)((void*)(x+y))

#include "../../../Include/driver/windows.h"
#include <stdio.h>
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



typedef BOOL (writeprocessmemory)(HANDLE hProcess, LPVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesWritten) // pointer function to WriteProcessMemory



char* GetSource(const char* Fname);
int GetFileSizeEX(const char* Fname);
ParseInfo* ManualMapPEHeader(const char* src, const char* pname);
int WriteHeaders(char* src, ParseInfo* info, void* wpm);
int GetFirstSection(ParseInfo* info);
int BaseRelocate(ParseInfo* info);
DWORD GetDynamicFunctionAddress(const char* src, const char* functionName);



#else
#error "parse.h is invalid for this kernel."

#endif

#endif