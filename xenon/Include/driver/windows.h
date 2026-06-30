#ifndef NTapi
#define NTapi

#if defined(_WIN32)

#include <windows.h>

typedef struct
{
	
	IMAGE_DOS_HEADER IMAGEDOSHEADER;
	IMAGE_NT_HEADERS IMAGENTHEADER;
	IMAGE_OPTIONAL_HEADER IMAGEOPTINALHEADER;
	IMAGE_FILE_HEADER IMAGEFILEHEADER;
	IMAGE_SECTION_HEADER IMAGESECTIONHEADER;

} PE_HEADER;

#else

#error "parse.h cannot be used in this kernel."

#endif
#endif
