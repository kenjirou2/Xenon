#include "helper.h"


int GetPID(const char* Pname)
{

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "\n\afailed to take a snapshot of process");
		return -1;
	}

	PROCESSENTRY32 pPE32;
	pPE32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(snapshot, &pPE32))
	{
		fprintf(stderr, "\nfailed to get first process");
		return -1;
	}

	do
	{
		if (strcmp(pe32.szExeFile, Pname) == 0)
		{
			CloseHandle(snapshot);
			return pe32.th32ProcessID;
		}

	} while (Process32Next(snapshot, &pPE32));
	
	fprintf(stderr, "\n\aerror: process must be loaded to start the manual mapper");
	return -1;

}

int GetHandle(int PID)
{

	HANDLE phandle = OpenProcess(PROCESS_ALL_ACCESS, false, PID);
	if (phandle == NULL)
	{
		fprintf(stderr, "\n\afailed to get process handle");
		return -1;
	}

	return phandle;

}