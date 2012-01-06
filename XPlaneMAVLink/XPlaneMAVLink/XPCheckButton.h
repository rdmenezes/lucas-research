/* Specialisation of the XPButton object for check buttons
 *	Sets the xpProperty_ButtonType to xpRadioButton and provides
 *	functions for checking and forcing selection
 */

#ifndef XPCheckButton_h
#define XPCheckButton_h

#include "XPButton.h"

class XPCheckButton : public XPButton {
public:
	XPCheckButton(XPObject *parent, const char * label, int x, int y, int width, int height);
	XPCheckButton(const char * label, int x, int y, int width, int height);
	bool isSelected();
	void setSelected(bool flag);

	/* Allows the user to set a callback on button press */
	void setStateChangedCallback(int (*stateChangedCallback)(XPCheckButton *b));
private:
	void init();

	/* Button pressed callback for our object */
	int (*scc)(XPCheckButton *b);

	/* Generic button pressed callback for all buttons */
	static int callback(XPWidgetMessage inMessage, XPWidgetID inWidget, long inParam1, long inParam2);
};

#endif