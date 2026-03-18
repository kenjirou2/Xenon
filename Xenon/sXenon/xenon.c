#include <stdio.h>
#include <string.h>
#include <stdint.h>
//#include "Dependencies/driver/memory.h"
#include "Dependencies/driver/socket.h"
#include "Dependencies/driver/windows.h"
//#include "Dependencies/IP/ip.h"
//#include "Dependencies/protohttp/protohttp.h"

void Xterminal();

#define KILOBYTE 1024

int main()
{

	Xterminal();


	return 0;

}

/*
SOCKET socket()
{




}

int SocBL()
{


}

int ConACC()
{



}


int cmdsend()
{






}


int datarecv()
{

	


}

void VersionGET()
{

	

	
}
*/
void Xterminal()
{

	uint16_t PORT = 0;
	WORD IP[4];
	char hostname[256];


	if(gethostname(hostname, sizeof(hostname)) != 0)
	{
		perror("\nFailed to get host name");
		return;
	}


	while (PORT == 0)
	{
		printf("┌─[%s]-[~/Xenon]\n└──╼ $\n", hostname);
		scanf("%hu", &PORT);
	}



}