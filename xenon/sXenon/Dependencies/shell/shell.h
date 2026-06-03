#ifndef SHELL_H
#define SHELL_H

#define Exit 2

#include "../XenonH/xenonhelper.h"

extern int PORT;
extern int ID;

int __init();
int __pexec(SOCKET socket);
int __pexec_ex(int ID);

#endif