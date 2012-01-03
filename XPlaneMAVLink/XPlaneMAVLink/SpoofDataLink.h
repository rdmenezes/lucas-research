#ifndef SpoofDataLink_h
#define SpoofDataLink_h

#include <string.h>
#include "DataLink.h"

class SpoofDataLink : public DataLink {
public:
	__declspec( dllexport ) SpoofDataLink(const char * input, int iSize, const char * output, int oSize);
	__declspec( dllexport ) SpoofDataLink(const char * buffer, int size);
	__declspec( dllexport ) bool connect();
	__declspec( dllexport ) bool send(char * message, int bytes);
	__declspec( dllexport ) int receive(int bytes, char * message);
	__declspec( dllexport ) bool disconnect();
private:
	const char * input;
	const char * output;
	int iSize;
	int oSize;
};

#endif