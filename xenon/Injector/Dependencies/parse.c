#include "parse.h"

errcode status;


int GetSource(const char* Fname, pPE_HEADER PEH)
{

	status = ERROR;

	PEH = malloc(sizeof(PEH));
	if (PEH == NULL)
	{
		fprintf(stderr, "\nfailed to allocate memory for PE Header shadow struct");
		return ERROR;
	}

	FILE* file = fopen(Fname, "rb");
	if (file == NULL)
	{
		fprintf(stderr, "\n\afailed to open file.");
		free(PEH)
		return ERROR;
	}

	int readf = fread(&PEH->IMAGEDOSHEADER, 1, sizeof(IMAGE_DOS_HEADER), file);
	if (readf != sizeof(IMAGE_DOS_HEADER))
	{
		fprintf(stderr, "\n\afailed to read from file.");
		free(PEH);
		fclose(file);
		return ERROR;
	}

	return status;

}

int parseDOSHeader(pPE_HEADER PEH, FILE* file)
{

	status = ERROR;

	if (PEH->IMAGEDOSHEADER->e_magic != IMAGE_DOS_SIGNATURE)
	{
		fprintf(stderr, "\nIncorrect Image Signature.");
		free(PEH);
		fclose(file);
		status = INVALID_DOS_SIGNATURE;
		return status;
	}

	if (!PEH->IMAGEDOSHEADER->e_lfanew)
	{
		fprintf(stderr, "\nNT struct offset does not exist");
		free(PEH);
		fclose(file);
		status = INVALID_NT_OFFSET;
		return status;
	}
	
	fclose(file);

	status = OK;
	return status;

}

int parseNTHeader(PE_HEADER PEH)
{

	status = ERROR;
	PEH = (PEH->IMAGEDOSHEADER + PEH->IMAGEDOSHEADER->e_lfanew);

	if (PEH->IMAGENTHEADER->Signature != IMAGE_NT_SIGNATURE)
	{
		fprintf(stderr, "\n\ainvalid match for PE signature");
		free(PEH);
		status = INVALID_NT_SIGNATURE;
		return status;
	}

	status = OK;
	return status;

}