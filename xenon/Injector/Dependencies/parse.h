#ifndef PARSER_H
#define PARSER_H


#if defined(_WIN32)

#include "../../Include/driver/windows.h"


#define IMAGE_NT_SIGNATURE 0x50450000


typedef enum
{

	ERROR = (int)0x0A,
	INVALID_DOS_SIGNATURE = (int)0x01,
	INVALID_NT_SIGNATURE = (int)0x02,
	INVALID_NT_OFFSET = (int)0x03,
	OK = (int)0x00,
	Exit = (int)0x99

} errcode;

typedef struct
{

	int NToffset;


} ParsedInfo;



char* GetSource(const char* Fname, pPE_HEADER PEH);
int GetFileSize(const char* Fname);
int ParsePEHeader(char* src, ParseInfo* info);

#else
#error "parse.h is invalid for this kernel."

#endif

#endif