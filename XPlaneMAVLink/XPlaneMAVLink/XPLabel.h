#ifndef XPLabel_h
#define XPLabel_h

#include <stdio.h>
#include "XPObject.h"
#include "XPStandardWidgets.h"

class XPLabel : public XPObject {
public:
	XPLabel(const char * text, int x, int y, int width, int height);
	XPLabel(XPObject * parent, const char * text, int x, int y, int width, int height);
	void setText(const char * text);
};

#endif