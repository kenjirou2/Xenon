#ifndef ipv
#define ipv

#include <stdio.h>
#include <stdint.h>


char* ipv4cmp(char ip)
{

	uint32_t SzIp = strlen(ip);
	if  (SzIp > 32 || SzIp < 32)
	{
		return "In func::ipv4cmp::string is not an ipv4 addrress:::";
	}
	

	if (ip[0] == '1' && ip[1] == '9' && ip[2] == '2' && ip[3] == '.' && ip[4] == '1' && ip[5] == '6' && ip[6] == '8')
	{
			
		return "String is an ipv4 addrress";

	}

	if (ip == NULL)
	{
		return "In func::ipv4cmp::no string passed:::";
	}
	

}




#endif