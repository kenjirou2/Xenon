#ifndef DOS_H
#define DOS_H

#include "../../../Include/protohttp/protohttp.h"

struct WEBSITESTATUS
{

	enum HTTPCODE status;
	size_t rcount;

};

#if defined(_WIN32)
/*






*/

#else

#error "this library is invalid for this kernel."

#endif


#endif