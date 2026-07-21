#include "parse.h"

int main(void)
{
    
    DWORD addr = DynamicFunctionLoad("C:/Windows/System32/kernel32.dll", "CreatePocessA");
    if (!addr) {return -1;}
    printf("offset %ld", addr);
    return 0;
    
}