#include "XPWindow.h"

/* Initialise the static members for keeping track of window objects */
int XPWindow::numberOfWindows=0;
XPWindow* XPWindow::windows[256];

/* Constructor, largely responsible for calling constructor on superclass
 *	Also defaults the window to be closable, sets the close callback to NULL
 *	and adds the new window to the static trackers
 */
XPWindow::XPWindow(const char * title, int x, int y, int width, int height) :
XPObject(title,x,y,width,height,NULL,xpWidgetClass_MainWindow) {
	setClosable(true);
	wcc = NULL;
	windows[numberOfWindows++] = this;
}

/* Allows the user to define whether the window should be closeable
 *	If not, there is no way to deregister the callback, but there's no
 *	chane of it firing
 */
void XPWindow::setClosable(bool flag) {
	if (flag) {
		XPSetWidgetProperty(getID(), xpProperty_MainWindowHasCloseBoxes,1);
		XPAddWidgetCallback(getID(), reinterpret_cast<XPWidgetFunc_t>(XPWindow::closeWindowCallback));
	} else {
		XPSetWidgetProperty(getID(), xpProperty_MainWindowHasCloseBoxes,0);
	}
}

/* Private function which is called on all window close events (not just ours)
 *	Hides the window, then iterates over all windows to find our ID
 *	If our window has a windowCloseCallback specified then it is called
 *	with our object as a parameter and the callbacks return value returned.
 *	Otherwise nothing happens and 0 is returned.
 */
int XPWindow::closeWindowCallback(XPWidgetMessage inMessage, XPWidgetID inWidget, long inParam1, long inParam2) {
	if (inMessage == xpMessage_CloseButtonPushed) {
		XPHideWidget(inWidget);
		for (int i=0; i<numberOfWindows; i++) {
			if (inWidget == windows[i]->getID()) {
				if (windows[i]->wcc != NULL) {
					return (windows[i]->wcc(windows[i]));
				}
			}
		}
	}
	return 0;
};