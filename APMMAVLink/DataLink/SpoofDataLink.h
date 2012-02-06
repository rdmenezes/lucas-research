#ifndef SpoofDataLink_h
#define SpoofDataLink_h

#include <stdio.h>
#include <string.h>
#include "DataLink.h"

#ifdef _WIN32
	class __declspec( dllexport ) SpoofDataLink : public DataLink {
#else
	class SpoofDataLink : public DataLink {
#endif
public:
	SpoofDataLink(const char * input, int iSize, const char * output, int oSize);
	SpoofDataLink(const char * buffer, int size);
	bool connect();
	bool send(char * message, int bytes);
	int receive(int bytes, char * message);
	bool disconnect();

private:
	const char * input;
	const char * output;
	int iSize;
	int oSize;
};

#endif
