#include <stdio.h>
#include "../Dependencies/Xenon/xenon.h"
#include "../Dependencies/XenonH/xenonhelper.h"
#include "../Dependencies/Xenon/shell.h"

addrctx CTX;

int main()
{
	int ID = __init();
	__pexec(ID);
	return 0; 
}