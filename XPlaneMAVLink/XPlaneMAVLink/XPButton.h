/* Wrapper for the XPlane xpWidgetClass_Button Widget
 *	Inherits XPObject for generic positioning
 *	Object may be instantiated inside a parent
 *	A button pressed callback may be specified
 *	Callback functionality is identical to XPWindow
 */

#ifndef XPButton_h
#define XPButton_H

#include "XPObject.h"
#include "XPStandardWidgets.h"

class XPButton : public XPObject {
public:
	/* Parentless constructor */
	XPButton(const char * label, int x, int y, int width, int height);

	/* Parent constructor */
	XPButton(XPObject *parent, const char * label, int x, int y, int width, int height);

	/* Allows the user to set a callback on button press */
	void setButtonPressedCallback(int (*buttonPressedCallback)(XPButton *b));
private:
	/* Initialisation function called by all constructors */
	void init();

	/* Button pressed callback for our object */
	int (*bpc)(XPButton *b);

	/* Generic button pressed callback for all buttons */
	static int callback(XPWidgetMessage inMessage, XPWidgetID inWidget, long inParam1, long inParam2);
protected:
	/* Variables to track our buttons */
	static int numberOfButtons;
	static XPButton* buttons[256];
};

#endif