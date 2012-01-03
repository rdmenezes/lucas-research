#ifndef DebugDataLink_h
#define DebugDataLink_h

#include <stdio.h>
#include "FileDataLink.h"

class DebugDataLink : public FileDataLink {
public:
	__declspec( dllexport ) DebugDataLink() : FileDataLink(stdout, stdin) {}
};

#endif