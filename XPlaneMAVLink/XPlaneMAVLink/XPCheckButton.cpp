#include "XPCheckButton.h"

/* Constructor if button has a parent */
XPCheckButton::XPCheckButton(XPObject *parent, const char * label, int x, int y, int width, int height) : 
XPButton(parent,label,x,y,width,height) {
	init();
}

/* Constructor for parentless button */
XPCheckButton::XPCheckButton(const char * label, int x, int y, int width, int height) : 
XPButton(label,x,y,width,height) {
	init();
}

/* Initialise button, set to be radio button (which is a checkbox ?!) */
void XPCheckButton::init() {
	XPSetWidgetProperty(getID(), xpProperty_ButtonType, xpRadioButton);
	XPSetWidgetProperty(getID(), xpProperty_ButtonBehavior, xpButtonBehaviorCheckBox);
	XPAddWidgetCallback(getID(), reinterpret_cast<XPWidgetFunc_t>(XPCheckButton::callback));
}

/* Is the button selected? */
bool XPCheckButton::isSelected() {
	return XPGetWidgetProperty(getID(),xpProperty_ButtonState,NULL);
}

/* Set button to be selected or not */
void XPCheckButton::setSelected(bool flag) {
	XPSetWidgetProperty(getID(),xpProperty_ButtonState,flag);
}

/* Let the user specify a callback function */
void XPCheckButton::setStateChangedCallback(int (*stateChangedCallback)(XPCheckButton *b)) {
	scc = stateChangedCallback;
}

/* Fire the button pressed callback for all buttons (functionally identical
 *	to the window close callback in XPWindow)
 */
int XPCheckButton::callback(XPWidgetMessage inMessage, XPWidgetID inWidget, long inParam1, long inParam2) {	
	for (int i = 0; i<numberOfButtons; i++) {
		if (inWidget == buttons[i]->getID()) {
			if (((XPCheckButton*)buttons[i])->scc != NULL) {
				if (inMessage == xpMsg_ButtonStateChanged) {
					((XPCheckButton*)buttons[i])->scc(((XPCheckButton*)buttons[i]));
				}
			}
		}
	}
	return 0;
}