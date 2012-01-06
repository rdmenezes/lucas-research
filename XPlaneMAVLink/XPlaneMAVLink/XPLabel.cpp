#include "XPLabel.h"

XPLabel::XPLabel(const char * text, int x, int y, int width, int height) :
XPObject(text,x,y,width,height,NULL,xpWidgetClass_Caption) {}

XPLabel::XPLabel(XPObject * parent, const char * text, int x, int y, int width, int height) :
XPObject(text,x,y,width,height,parent,xpWidgetClass_Caption) {}

void XPLabel::setText(const char * text) {
	XPSetWidgetDescriptor(getID(),text);
}