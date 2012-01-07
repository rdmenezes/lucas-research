#include "XPButton.h"

/* Initialise tracking variables */
int XPButton::numberOfButtons = 0;
XPButton *XPButton::buttons[256];

/* Initialise the button
 *	Add it to the trackers, NULLify the callback and register with XPlane
 */
void XPButton::init() {
	buttons[numberOfButtons++] = this;
	bpc = NULL;
	XPAddWidgetCallback(getID(), reinterpret_cast<XPWidgetFunc_t>(XPButton::callback));
}

/* Constructor if button has a parent */
XPButton::XPButton(XPObject *parent, const char * label, int x, int y, int width, int height) : 
XPObject(label,x,y,width,height,parent,xpWidgetClass_Button) {
	init();
}

/* Constructor if button has no parent */
XPButton::XPButton(const char * label, int x, int y, int width, int height) : 
XPObject(label,x,y,width,height,NULL,xpWidgetClass_Button) {
	init();
}

/* Let the user specify a callback function */
void XPButton::setButtonPressedCallback(int (*buttonPressedCallback)(XPButton *b)) {
	bpc = buttonPressedCallback;
}

/* Fire the button pressed callback for all buttons (functionally identical
 *	to the window close callback in XPWindow)
 */
int XPButton::callback(XPWidgetMessage inMessage, XPWidgetID inWidget, long inParam1, long inParam2) {	
	for (int i = 0; i<numberOfButtons; i++) {
		if (inWidget == buttons[i]->getID()) {
			if (buttons[i]->bpc != NULL) {
				if (inMessage == xpMsg_PushButtonPressed) {
					buttons[i]->bpc(buttons[i]);
				}
			}
		}
	}
	return 0;
}