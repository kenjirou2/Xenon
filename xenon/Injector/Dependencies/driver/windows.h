#ifndef NTapi
#define NTapi

#include <windows.h>

typedef struct{
	
	IMAGE_DOS_HEADER IMDOSHeader;
	IMAGE_NT_HEADERS IMNTHeader;
	IMAGE_OPTIONAL_HEADER IMOptionalHeader;
	IMAGE_FILE_HEADER IMFileHeader;
	IMAGE_SECTION_HEADER IMSectionHeader;

} PE_HEADER;


#endif