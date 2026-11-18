#include "Dependencies/parse/parse.h"

int main(void)
{
    ParseInfo* parsed = malloc(sizeof(ParseInfo));
    if (parsed == NULL) { return -1; }
    parsed = ManualMapPEHeader(GetSource("test.exe"), GetPID("test.exe"));
    if (parsed == ERROR){
        fprintf(stderr, "error: Manual Mapper Error");
        return -1;
    }

    DWORD addr = DynamicFunctionLoad(KERNEL32DLL, "LoadLibraryA");
    if (addr == 1 || addr == 2)
    {
        printf("\nfailed to get function address");
        return -1;
    }
    printf("%lu", addr);
    return 0;
}