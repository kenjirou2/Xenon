#ifndef SHELL_H
#define SHELL_H

#include "../XenonH/xenonhelper.h"

#define Exit 2
int PORT = 0;
int ID = -1;

int __init();
int __pexec(int ID);

#endif