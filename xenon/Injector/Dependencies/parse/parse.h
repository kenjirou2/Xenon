#ifndef PARSER_H
#define PARSER_H


#if defined(_WIN32)

#include "../../Include/driver/windows.h"


#define IMAGE_NT_SIGNATURE 0x50450000


typedef enum
{

	ERROR = (int)0xA,
	INVALID_DOS_SIGNATURE = (int)0x01,
	INVALID_NT_SIGNATURE = (int)0x02,
	INVALID_NT_OFFSET = (int)0x03,
	ALLOCATION_FAILURE = (int)0x04,
	PARSE_INFO_EMPTY = (int)0x05,
	HEADER_COPY_FAILED = (int)0x06,
	SECTION_COPY_FAILED = (int)0x07,
	REBASE_FAILED = (int)0x09,

	OK = (int)0x00,
	Exit = (int)0x99

} errcode;

typedef struct
{

	errcode result;

	int* OptionalHeaderAddress;

	int NToffset;
	DWORD sizeofimage;
	DWORD oldimagebase;
	WORD numberofsections;
	DWORD sizeofheaders;
	int sizeofoptinalheader;
	HMODULE newimagebase;

	int PID;
	HANDLE pHandle;
	const char* pname;

} ParseInfo;



char* GetSource(const char* Fname, pPE_HEADER PEH);
int GetFileSize(const char* Fname);
ParseInfo* ManualMapPEHeader(char* src);
int WriteHeaders(ParseInfo* info);
int GetFirstSection(ParseInfo* info);
int BaseRelocate(ParseInfo* info);



#else
#error "parse.h is invalid for this kernel."

#endif

#endif