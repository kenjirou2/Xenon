#ifndef PARSER_H
#define PARSER_H

#include "../../Include/driver/windows.h"



#define IMAGE_DOS_SIGNATURE 0x4D5A
#define IMAGE_NT_SIGNATURE 0x50450000

typedef enum
{

	INVALID_DOS_SIGNATURE = (int)0x01,
	INVALID_NT_SIGNATURE = (int)0x02,
	Exit = (int)0x99

} errcode;



char* GetSource(char* Fname);
int parseDOSHeader(const char* src);
int parseNTHeader(int ntoffset, const char* src);
int parserOPTIONALHeader(const char* src);


#endif