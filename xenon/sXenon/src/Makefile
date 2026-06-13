export TMP := /tmp
export TEMP := /tmp
export TMPDIR := /tmp

Xenon.exe: Xenon.c
	cc -Wall -Wextra -Werror \
		Xenon.c \
		misc/menu.c \
		misc/version.c \
		../Dependencies/Xenon/xenon.c \
		../Dependencies/XenonH/xenonhelper.c \
		../Dependencies/Shell/shell.c \
		../../Include/protohttp/protohttp.c \
		-o Xenon.exe \
		-lws2_32 \
		-lssl \
		-lcrypto
		
Xenon.o : Xenon.cc
	cc -Wall -Wextra -Werror \
	Xenon.c \
	misc/menu.c \
	misc/version \
	../Dependencies/Xenon/xenon.c \
	../Dependencies/XenonH/xenonhelper.c \
	../Dependencies/Shell/shell.c \
	../../Include/protohttp/protohttp.c \
	-o Xenon.o \
	-lws2_32 \
	-lssl \
	-lcrypto
	
xenon.o : ../Dependencies/Xenon/xenon.c
	cc -Wall -Wextra -Werror \
	-c ../Dependencies/Xenon/xenon.c
	
	