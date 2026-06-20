#ifndef IP_H
#define IP_H

int ipcmp(const char* ip)
{
    int a, b, c, d;
    char extended;
    if (sscanf(ip, "%d.%d.%d.%d%c", &a, &b, &c, &d, &extended) != 4)
    {
        return -1;
    }
    return 0;
}

#endif
