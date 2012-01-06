#include "XPObject.h"

/* Constructor for a generic object
 *	Takes a description, geometry (relative to parent), parent object and XPlane Widget type
 */
XPObject::XPObject(const char* description, int x, int y, int width, int height, XPObject *parent, XPWidgetClass objClass) {
	int isRoot = 0;
	XPWidgetID root = 0;
	if (parent == NULL) {
		isRoot = 1;
	} else {
		root = parent->getID();
	}
	this->parent = parent;
	objID = XPCreateWidget(0,0,0,0,0,description,isRoot,root,objClass);
	setGeometry(x,y,width,height);
}

/* Geometry setters which all call 'setGeometry' */
void XPObject::setX(int x) {
	setGeometry(x,getY(),getWidth(),getHeight());
}
void XPObject::setY(int y) {
	setGeometry(getX(),y,getWidth(),getHeight());
}
void XPObject::setWidth(int width) {
	setGeometry(getX(),getY(),width,getHeight());
}
void XPObject::setHeight(int height) {
	setGeometry(getX(),getY(),getWidth(),height);
}

/* Visibility setter calls XPlane widget library directly */
void XPObject::setVisible(bool visible) {
	if (visible) {
		XPShowWidget(objID);
	} else {
		XPHideWidget(objID);
	}
}

/* Geometry getters for both relative (to parent) and absolute
 *	(relative to screen) positions
 */
int XPObject::getX() {
	int x, y, width, height;
	getGeometry(x,y,width,height);
	return x;
}
int XPObject::getY() {
	int x, y, width, height;
	getGeometry(x,y,width,height);
	return y;
}
int XPObject::getAbsoluteX() {
	int x, y, width, height;
	getAbsoluteGeometry(x,y,width,height);
	return x;
}
int XPObject::getAbsoluteY() {
	int x, y, width, height;
	getAbsoluteGeometry(x,y,width,height);
	return y;
}
int XPObject::getWidth() {
	int x, y, width, height;
	getGeometry(x,y,width,height);
	return width;
}
int XPObject::getHeight() {
	int x, y, width, height;
	getGeometry(x,y,width,height);
	return height;
}

/* Visibility getter */
bool XPObject::isVisible() {
	return(XPIsWidgetVisible(objID));
}

/* Getter for the Widget ID of this object */
XPWidgetID XPObject::getID() {
	return objID;
}

/* Getter for a pointer to the parent object */
XPObject *XPObject::getParent() {
	return parent;
}

/* Private setter and getter functions*/
/* Sets geometry relative to a parent object (rather than the XPlane way of
 * doing everything in screen coordinates
 */
void XPObject::setGeometry(int x, int y, int width, int height) {
	int pX = 0;
	int pY = 0;
	if (parent != NULL) {
		pX = parent->getAbsoluteX();
		pY = parent->getAbsoluteY();
	}
	setAbsoluteGeometry(pX+x,pY+y,width,height);
}

/* Sets the absolute position (screen coordinates) of an object,
 *	Uses width and height instead of bounding box coordinates
 */
void XPObject::setAbsoluteGeometry(int x, int y, int width, int height) {
	XPSetWidgetGeometry(objID,x,y+height,x+width,y);
}

/* Gets the objects location relative to a parent object */
void XPObject::getGeometry(int &x, int &y, int &width, int &height) {
	int pX = 0;
	int pY = 0;
	if (parent != NULL) {
		pX = parent->getAbsoluteX();
		pY = parent->getAbsoluteY();
	}
	getAbsoluteGeometry(x,y,width,height);
	x -= pX;
	y -= pY;
}

/* Gets the objects absolute location */
void XPObject::getAbsoluteGeometry(int &x, int &y, int &width, int &height) {
	int x1, y1, x2, y2;
	XPGetWidgetGeometry(objID,&x1,&y1,&x2,&y2);
	x = x1;
	height = y1-y2;
	y = y2;
	width = x2-x1;
}