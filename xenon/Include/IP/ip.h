#ifndef IP_H
#define IP_H

#define IPsize 4

int ipint(char* IP)
{
    int ip = 0;
    int num = 0;

    while (*IP)
    {
        if (*IP >= '0' && *IP <= '9')
        {
            num = num * 10 + (*IP - '0');
        }
        else if (*IP == '.')
        {
            ip = (ip << 8) | num;
            num = 0;
        }
        IP++;
    }

    ip = (ip << 8) | num;

    return ip;
}

int ipcmp(int IP)
{

	size_t size = sizeof(IP);
	if (size != IPsize)
	{
		return -1;
	}

	return 0;

}

#endif