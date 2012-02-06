/* Wrapper for the XPlane xpWidgetClass_MainWindow Widget
 *	Inherits the XPObject class for basic positioning functionality
 *	Allows closable property to be modified (add or remove close buttons)
 *	If set to closable the window registers a callback with XPlane that
 *	fires on close. This callback can be specified via the 'setWindowCloseCallback'
 *	function
 */

#ifndef XPWindow_h
#define XPWindow_h

#include "XPObject.h"
#include "XPStandardWidgets.h"

class XPWindow : public XPObject {
public:
	/* Constructor */
	XPWindow(const char * title, int x, int y, int width, int height);
	
	/* Set closable property */
	void setClosable(bool flag);

	/* Set the window close callback */
	void setWindowClosedCallback(int (*windowClosedCallback)(XPWindow *w));
private:
	/* User specified callback for window close */
	int (*wcc)(XPWindow *b);

	/* Internal callback for all windows, finds window which matches and calls
	 * its specific callback
	 */
	static int closeWindowCallback(XPWidgetMessage inMessage, XPWidgetID inWidget, long inParam1, long inParam2);
	
	/* Some variables to keep track of window objects */
	/* Note the arbitrary maximum number of windows is 256 */
	static int numberOfWindows;
	static XPWindow* windows[256];
};

#endif