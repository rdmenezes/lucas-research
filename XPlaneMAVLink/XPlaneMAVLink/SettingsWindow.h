/* A class which combines the functions of a XPWindow and the Settings wrapper
 *	Allows us to create a pop up window to give the user access to the settings
 *	NOTE: This wasn't written very well!
 *	TODO: Tidy all this up!
 */


#ifndef SettingsWindow_h
#define SettingsWindow_h

#include "Settings.h"
#include "XPWindow.h"
#include "XPCheckButton.h"
#include "XPTextField.h"
#include "XPLabel.h"


static class SettingsWindow : public XPWindow, public Settings {
public:
	/* Constructor */
	SettingsWindow();

	/* Show an error message */
	void error(const char * msg);
	
	/* Open our window */
	void open();

	/* Specify a callback */
	void setSaveCallback(int (*saveCallback)(SettingsWindow *w));
private:
	
	/* Lots of static things to get the callbacks to work! */
	static SettingsWindow * myWindow;
	static void tcpVisible(bool flag);
	static void serialVisible(bool flag);
	static int interfaceCallback(XPCheckButton *me);
	static int okCallback(XPButton *me);
	static int cancelCallback(XPButton *me);
	static bool validateTCP();
	static bool validateSerial();

	static XPCheckButton *tcpButton;
	static XPLabel *ipLabel;
	static XPTextField *ipField;
	static XPLabel *portLabel;
	static XPTextField *portField;

	static XPCheckButton *serialButton;
	static XPLabel *comLabel;
	static XPTextField *comField;
	static XPLabel *baudLabel;
	static XPTextField *baudField;

	static XPButton *okButton;
	static XPButton *cancelButton;

	int (*scb)(SettingsWindow *w); 


};

#endif