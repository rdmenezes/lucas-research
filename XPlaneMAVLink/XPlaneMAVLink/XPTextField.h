#ifndef XPTextField_h
#define XPTextField_h

#include "XPObject.h"
#include "XPStandardWidgets.h"

class XPTextField : public XPObject {
public:
	XPTextField(XPObject * parent, int x, int y, int width, int height);
	XPTextField( int x, int y, int width, int height);
	const char * getValue();
	void setValue(const char * value);
};

#endif