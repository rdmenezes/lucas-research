#ifndef DebugDataLink_h
#define DebugDataLink_h

#include <stdio.h>
#include "FileDataLink.h"

class DebugDataLink : public FileDataLink {
public:
#ifdef _WIN32
	__declspec( dllexport ) DebugDataLink() : FileDataLink(stdout, stdin) {}
#else
	DebugDataLink() : FileDataLink(stdout, stdin) {}
#endif
};

#endif
