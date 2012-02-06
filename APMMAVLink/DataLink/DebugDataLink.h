#ifndef DebugDataLink_h
#define DebugDataLink_h

#include <stdio.h>
#include "FileDataLink.h"

#ifdef _WIN32
	class __declspec( dllexport ) DebugDataLink : public FileDataLink {
#else
	class DebugDataLink : public FileDataLink
#endif
public:
	DebugDataLink() : FileDataLink(stdout, stdin) {}
};

#endif
