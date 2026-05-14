#ifndef IPV4_H
#define IPV4_H

bool ipv4cmp(const char* ip)
{
    if (!ip) { return 0; }

    int d1, d2, d3, d4;
    char trail;

    if (sscanf(ip, "%d.%d.%d.%d%c", &d1, &d2, &d3, &d4, &trail) != 4)  { return 1; }

    if
	(
		d1 < 0 || d1 > 255 ||
        d2 < 0 || d2 > 255 ||
        d3 < 0 || d3 > 255 ||
        d4 < 0 || d4 > 255
	) { return 0; }

    return 1;
}

#endif
