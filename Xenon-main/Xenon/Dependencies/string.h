#ifndef STRING_H
#define STRING_H

#include <stdio.h>

unsigned int strleng(const char *str)
{
	int i = 0;
		
	while (str[i] != '\0')
	{
		i++;
	}

	return i;

}

/*
static char* strcpy(const char str1, const char str2)
{

	while (*str2 != '\0')
	{
		*str1 = *str2;
		str1++;
		str2++;
	}

	*str1 = '\0';
	return str1;

}
*/

int charstrcmp(const char chr, const char* str)
{
		
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == chr)
		{
			return 0;
		}
		i++;

	}
	return 1;
}

int strcomp(const char* str1, const char* str2)
{

	int i = 0;

	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i]){return 1;}
		i++;
	}
	if (str1[i] != str2[i]){return 1;}
	i++;

	return 0;

}

int strccmp(const char str1[0], const char str2[0])
{
	while (str1[0] != '\0' && str2[0] != '\0')
	{
		if (str1[0] == str2[0])
		{
			return 0;
		}
		return 1;
	}
		
}

int strochr(const char chr, const char* str)
{
	int i = 0;
	while (chr != '\0' && str[i] != '\0')
	{
		if (chr == str[i])
		{
			return i;
		}
		i++;
	}
}

int strcmpstr(const char* str1, const char* str2)
{
	if (!str1 || !str2) return 1;
	if (str2[0] == '\0') return 1;

	for (int i = 0; str1[i] != '\0'; i++)
	{
		int j = 0;
		while (str2[j] != '\0' && str1[i + j] == str2[j])
		{
			j++;
		}
		if (str2[j] == '\0')
		{
			return 0;
		}
	}

	return -1;

}

char* intconv(int num, char* str)
{

	int i = 0;

	do
	{
		str[i++] = (num % 10) + '0';
		num /= 10;
	} while (num > 0);

	str[i] = '\0';

	for (int j = 0; j < i / 2; j++)
	{
		char t = str[j];
		str[j] = str[i - j - 1];
		str[i - j - 1] = t;

	}

	return str;


}









#endif