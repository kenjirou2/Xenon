#include "parse.h"

errcode status;


int GetSource(const char* Fname, PE_HEADER *PEH)
{

	status = ERROR;

	PEH = malloc(sizeof((PE_HEADER)PEH));
	if (PEH == NULL)
	{
		fprintf(stderr, "\nfailed to allocate memory.");
		return ERROR;
	}

	int openf = fopen(Fname, "rb");
	if (openf == NULL)
	{
		fprintf(stderr, "\nfailed to open file.");
		return ERROR;
	}

	int readf = read(PEH, 1, sizeof(PEH.IMAGE_DOS_HEADER), openf);
	if (readf < sizeof(PEH.IMAGE_DOS_HEADER))
	{
		fprintf(stderr, "\nfailed to read data from file.");
		return ERROR;
	}

	pPEH = &PEH;

	status = OK;
	return status;

}

int parseDOSHeader(pPE_HEADER PEH, FILE* file)
{

	status = ERROR;

	PEH = 

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