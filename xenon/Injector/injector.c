#include "Dependencies/parse/parse.c"

int main(void)
{
    
    ParseInfo* parsed = malloc(sizeof(ParseInfo));
    if (parsed == NULL) { return -1; }
    parsed = ManualMapPEHeader(GetSource("test.exe"), "test.exe");
    DWORD addr = DynamicFunctionLoad("kernel32.dll", "CreateFiles");
    if (addr == 1 || addr == 2)
    {
        printf("failed to get function address");
        return -1;
    }
    return 0;
}