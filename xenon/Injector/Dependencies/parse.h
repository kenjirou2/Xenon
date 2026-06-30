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
	OK = (int)0x00,
	Exit = (int)0x99

} errcode;



char* GetSource(const char* Fname, char* src, pPE_HEADER* DOS);
int parseDOSHeader(const char* src);
int parseNTHeader(int ntoffset, const char* src);
int parserOPTIONALHeader(const char* src);



#endif