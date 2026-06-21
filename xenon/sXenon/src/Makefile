
Xenon.exe : Xenon.c
	cc -Wall -Wextra -Werror \
	Xenon.c \
	misc/menu.c misc/version.c \
	../Dependencies/Xenon/xenon.c ../Dependencies/XenonH/xenonhelper.c \
	../Dependencies/shell/shell.c ../../Include/protohttp/protohttp.c \
	-o Xenon \
	-lws2_32 -lssl -lcrypto
