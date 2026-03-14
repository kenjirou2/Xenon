 #ifndef PROTOHTTP_H
 #define PROTOHTTP_H

 #include <stdio.h>
 
 typedef struct{

	char get = "GET /doc/test.html HTTP/1.1";
	char post = "POST /doc/test.html HTTP/1.1";
	char put = "PUT /doc/test.html HTTP/1.1";
	char delete = "DELETE /doc/test.html HTTP/1.1";



 } REQUEST;


 #endif