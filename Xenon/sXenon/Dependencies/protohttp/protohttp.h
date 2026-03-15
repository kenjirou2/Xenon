 #ifndef PROTOHTTP_H
 #define PROTOHTTP_H

 #include <stdio.h>
 #include <winsoch.h>

 typedef struct{

	char get = "GET /test.html HTTP/1.1";
	char post = "POST /test.html HTTP/1.1";
	char put = "PUT /test.html HTTP/1.1";
	char delete = "DELETE /test.html HTTP/1.1";

 } REQUEST;


char *httpbuild(char type, char HOST, char port)
{

	
	

}

char *httpconnect(char HOST, char port)
{



}

char *httpsend()
{


}

char httprec()
{


}




 #endif