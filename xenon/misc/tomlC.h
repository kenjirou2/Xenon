#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const char* trim(char* buffer)
{

	while (*buffer == ' ' || *buffer == '\t' || *buffer == '\n' || *buffer == '\r')
	{
		buffer++;
	}

	return buffer;

}

bool ChkTable(char* buffer)
{
	trim(buffer);
	if (strlen(buffer) < 3) { return 0; }
	if (buffer[0] != '[' || buffer[strlen(buffer) - 1] != ']') { return 0; }
	return 1;
}

const char* GetTableName(const char* buffer, char* name)
{

	if (ChkTable(buffer) != 1) { return NULL; }
	size_t blen = strlen(buffer);

	buffer++;
	int end = strchr(buffer, ']');
	int delta = end - buffer;

	strncpy(name, buffer, delta);
	name[len] = '\0';

	return name;

}