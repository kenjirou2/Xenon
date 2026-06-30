#ifndef PARSER_H
#define PARSER_H

#include "../../Include/driver/windows.h"


#define IMAGE_DOS_SIGNATURE 0x4D5A
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



char* GetSource(const char* Fname, pPE_HEADER PEH);

int parseDOSHeader(pPE_HEADER PEH, FILE* file);
int parseNTHeader(pPE_HEADER PEH);
int parserOPTIONALHeader(const char* src);



#endif