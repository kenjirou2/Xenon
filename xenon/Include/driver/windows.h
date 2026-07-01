#ifndef NTapi
#define NTapi

#if defined(_WIN32)

#include <windows.h>

typedef struct
{

	IMAGE_DOS_HEADER;
	IMAGE_NT_HEADERS;
	IMAGE_OPTIONAL_HEADER;
	IMAGE_FILE_HEADER;
	IMAGE_SECTION_HEADER;

} PE_HEADER;

#else

#error "windows.h cannot be used in this kernel."

#endif
#endif
