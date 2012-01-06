#include "XPTextField.h"

XPTextField::XPTextField(XPObject * parent, int x, int y, int width, int height) :
XPObject("",x,y,width,height,parent,xpWidgetClass_TextField) {}

XPTextField::XPTextField(int x, int y, int width, int height) :
XPObject("",x,y,width,height,NULL,xpWidgetClass_TextField) {}

const char * XPTextField::getValue() {
	char desc[256];
	XPGetWidgetDescriptor(getID(),desc,256);
	return desc;
}

void XPTextField::setValue(const char * value) {
	XPSetWidgetDescriptor(getID(),value);
}