#include "SettingsWindow.h"

/* Declare all of our statis members */
XPCheckButton *SettingsWindow::tcpButton;
XPLabel *SettingsWindow::ipLabel;
XPTextField *SettingsWindow::ipField;
XPLabel *SettingsWindow::portLabel;
XPTextField *SettingsWindow::portField;

XPCheckButton *SettingsWindow::serialButton;
XPLabel *SettingsWindow::comLabel;
XPTextField *SettingsWindow::comField;
XPLabel *SettingsWindow::baudLabel;
XPTextField *SettingsWindow::baudField;

XPButton *SettingsWindow::okButton;
XPButton *SettingsWindow::cancelButton;
SettingsWindow *SettingsWindow::myWindow;

/* Initialise the window */
SettingsWindow::SettingsWindow() : XPWindow("MAVLink Settings", 200, 100, 400, 250) , 
	Settings("MAVLink.txt") {

	int height = 250;	//How high are we
	int line = 18;		//How high is a line
	myWindow = this;	//Instance variable to keep track of ourselves (for callbacks)
	height -= 30;		//Make ourselves smaller to take acount of top bar

	/* Print a title */
	XPLabel *title = new XPLabel(this,"Choose which interface X-Plane should output MAVLink Messages to",20,height-line,400,line);
	title->setVisible(true);

	/* Add a check box to let the user select a TCP connection */
	tcpButton = new XPCheckButton(this,"",20,height-3*line,20,line);
	tcpButton->setVisible(true);
	tcpButton->setStateChangedCallback(SettingsWindow::interfaceCallback);
	XPLabel *tcpLabel = new XPLabel(this,"TCP Connection",40,height-3*line,100,line);
	tcpLabel->setVisible(true);

	/* Add the IP address as a parameter which the user can edit */
	/* This defaults to not visible unless it is enabled */
	ipLabel = new XPLabel(this,"IP Address:",36,height-4*line,65,line);
	ipField = new XPTextField(this,100,height-4*line,100,line);
	char ipStr[128];
	sprintf(ipStr,"%s",getIP());
	ipField->setValue(ipStr);

	/* Add the port as a parameter which the user can edit */
	/* This defaults to not visible unless it is enabled */
	portLabel = new XPLabel(this,"Port:",70,height-5*line,30,line);
	portField = new XPTextField(this,100,height-5*line,60,line);
	char portStr[10];
	sprintf(portStr,"%d",getPort());
	portField->setValue(portStr);

	/* Add a check box to let the user specify a serial connection */
	serialButton = new XPCheckButton(this,"",20,height-7*line,20,line);
	serialButton->setVisible(true);
	serialButton->setStateChangedCallback(SettingsWindow::interfaceCallback);
	XPLabel *serialLabel = new XPLabel(this,"Serial Port",40,height-7*line,100,line);
	serialLabel->setVisible(true);

	/* Let the user choose a com port, defaults to invisible */
	comLabel = new XPLabel(this,"Com Port:",42,height-8*line,65,line);
	comField = new XPTextField(this,100,height-8*line,60,line);
	char comStr[128];
	sprintf(comStr,"%s",getComPort());
	comField->setValue(comStr);

	/* Let the user choose a baud rate, defaults to invisible */
	baudLabel = new XPLabel(this,"Baud Rate:",35,height-9*line,65,line);
	baudField = new XPTextField(this,100,height-9*line,60,line);
	char baudStr[128];
	sprintf(baudStr,"%d",getBaudRate());
	baudField->setValue(baudStr);

	/* OK and Cancel Buttons */
	okButton = new XPButton(this,"OK",40,20,40,20);
	okButton->setVisible(true);
	okButton->setButtonPressedCallback(SettingsWindow::okCallback);

	cancelButton = new XPButton(this,"Cancel",120,20,40,20);
	cancelButton->setVisible(true);
	cancelButton->setButtonPressedCallback(SettingsWindow::cancelCallback);

	/* If we're in TCP mode (defined by out Settings superclass), enable those fields */
	if (getFlag() == 1) {
		tcpVisible(true);
	}

	/* If we're in Serial mode (defined by out Settings superclass), enable those fields */
	if (getFlag() == 2) {
		serialVisible(true);
	}

	//Assume no close callback initially
	scb = NULL;

}

/* If something goes wrong, print an error message */
void SettingsWindow::error(const char * msg) {
	char labelText[512];
	sprintf(labelText,"%s", msg);
	int x, y, w, h;
	XPWindow *errWindow = new XPWindow("Error!",getAbsoluteX()+50, getAbsoluteY()+50,300,50);
	XPLabel *errLabel = new XPLabel(errWindow,msg,10,10,280,20);
	errWindow->setClosable(true);
	errLabel->setVisible(true);
	errWindow->setVisible(true);
}

/* Allow this window to be opened
 *	Loads in the parameters from the config file (inherited from the Settings superclass) first
 */
void SettingsWindow::open() {
	load();
	setVisible(true);
}

/* Allow someone to specify a callback for when we successfully save */
void SettingsWindow::setSaveCallback(int (*saveCallback)(SettingsWindow *w)) {
	scb = saveCallback;
}

/* Visibility toggles for the TCP and Serial fields */
void SettingsWindow::tcpVisible(bool flag) {
	tcpButton->setSelected(flag);
	ipLabel->setVisible(flag);
	ipField->setVisible(flag);
	portLabel->setVisible(flag);
	portField->setVisible(flag);
}
void SettingsWindow::serialVisible(bool flag) {
	serialButton->setSelected(flag);
	comLabel->setVisible(flag);
	comField->setVisible(flag);
	baudLabel->setVisible(flag);
	baudField->setVisible(flag);
}

/* Callback for toggling between TCP, Serial, and None
 *	If TCP is selected and Serial is clicked, TCP gets unselected and Serial is
 *	selected (and vice versa).
 *	If TCP is selected and TCP is clicked, it is deselected (i.e. "None" is selected)
 */
int SettingsWindow::interfaceCallback(XPCheckButton *me) {
	if (me == tcpButton) {
		tcpVisible(me->isSelected());
		serialVisible(false);
	} else if (me == serialButton) {
		tcpVisible(false);
		serialVisible(me->isSelected());
	}
	return 1;
}

/* Function called when user clicks OK 
 *	Validate user input (if any) and if valid save it
 */
int SettingsWindow::okCallback(XPButton *me) {
	if (tcpButton->isSelected()) {
		if (!validateTCP()) {
			return -1;
		}
	}
	if (serialButton->isSelected()) {
		if (!validateSerial()) {
			return -1;
		}
	}
	if (!tcpButton->isSelected() && !serialButton->isSelected()) {
		myWindow->setFlag(0);
	}
	myWindow->save();
	myWindow->setVisible(false);
	if (myWindow->scb != NULL) {
		myWindow->scb(myWindow);
	}
	return 1;
}

/* If the user clicks cancel, do nothing (don't save) */
int SettingsWindow::cancelCallback(XPButton *me) {
	myWindow->setVisible(false);
	return 1;
}

/* Has the user input valid TCP parameters?
 *	Parameters are validated in the Settings superclass
 *	This method generates the appropriate erros if invalid
 */
bool SettingsWindow::validateTCP() {
	char ip[128];
	sprintf(ip,"%s",ipField->getValue());
		
	int port;
	sscanf(portField->getValue(), "%d",&port);
	if (!myWindow->setIP(ip)) {
		myWindow->error("Invalid IP Address!");
		return false;
	}
	if (!myWindow->setPort(port)) {
		myWindow->error("Invalid Port!");
		return false;
	}
	myWindow->setFlag(1);
	return true;
}

/* Has the user input valid Serial parameters?
 *	Parameters are validated in the Settings superclass
 *	This method generates the appropriate erros if invalid
 */
bool SettingsWindow::validateSerial() {
	char com[128];
	sprintf(com,"%s",comField->getValue());
		
	int baud;
	sscanf(baudField->getValue(),"%d",&baud);
		
	if (!myWindow->setComPort(com)) {
		myWindow->error("Invalid IP Address!");
		return false;
	}
	if (!myWindow->setBaudRate(baud)) {
		myWindow->error("Invalid Port");
		return false;
	}
	myWindow->setFlag(2);
	return true;
}