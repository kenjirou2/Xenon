#include "parse.h"

errcode status;


int GetSource(const char* Fname, pPE_HEADER PEH)
{

	status = ERROR;

	FILE* file = fopen(Fname, "rb");
	if (file == NULL)
	{
		fprintf(stderr, "\n\afailed to open file.");
		return ERROR;
	}

	int readf = fread(&PEH->IMAGEDOSHEADER, 1, sizeof(IMAGE_DOS_HEADER), file);
	if (readf != sizeof(IMAGE_DOS_HEADER))
	{
		fprintf(stderr, "\n\afailed to read from file.");
		fclose(file);
		return ERROR;
	}

	return status;

}

int parseDOSHeader(const char* src, pPE_HEADER PEH, FILE* file)
{

	status = ERROR;

	if (PEH->IMAGEDOSHEADER->e_magic != IMAGE_DOS_SIGNATURE)
	{
		fprintf(stderr, "\nIncorrect Image Signature.");
		close(file);
		return status
	}

	if (!PEH->IMAGEDOSHEADER->e_lfanew)
	{
		fprintf(stderr, "\nNT struct offset does not exist");
		close(file);
		return ERROR;
	}

	status = OK;
	return status;

}

int 


