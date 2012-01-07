/* Wrapped class for the XPlane Widget API
 *	Describes a generic Object with bounds, parent object and visibility
 *	Shouldn't need to be used directly, but is inherited by all other objects
 */


#ifndef XPObject_h
#define XPObject_h

#include "XPWidgets.h"

class XPObject {
public:	
	XPObject(const char* description, int x, int y, int width, int height, XPObject *parent, XPWidgetClass objClass);
	void setX(int x);
	void setY(int y);
	void setWidth(int width);
	void setHeight(int height);
	void setVisible(bool visible);
	int getX();
	int getY();
	int getAbsoluteX();
	int getAbsoluteY();
	int getWidth();
	int getHeight();
	bool isVisible();
	XPWidgetID getID();
	XPObject *getParent();
private:
	void setGeometry(int x, int y, int width, int height);
	void setAbsoluteGeometry(int x, int y, int width, int height);
	void getGeometry(int &x, int &y, int &width, int &height);
	void getAbsoluteGeometry(int &x, int &y, int &width, int &height);
	XPWidgetID objID;
	XPObject *parent;
};

#endif