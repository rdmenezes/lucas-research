 /*
	Copyright (C) 2012 Owen McAree (LUCAS)

	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in
	the Software without restriction, including without limitation the rights to
	use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
	of the Software, and to permit persons to whom the Software is furnished to do
	so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

/* MAVLink Interface for X-Plane v0.8
 *	Written by Owen McAree (o.mcaree@lucasresearch.co.uk)
 *
 *	Designed for the purpose of connected Ardupilot Mega (APM) to X-Plane directly
 *	without requiring the Mission Planner for the purpose of developing Simulink
 *	based control.
 *	Has been tested as working with ArduPlane (APM in fixed wing mode) in Software
 *	In Loop (SIL) mode using HIL_ATTITUDE and X-Plane v9.70 running on Windows
 *	Work is ongoing to support Hardware In Loop (HIL), ArduCopter, and X-Plane on
 *	Linux.
 */


#define PI 3.14159
#define VERSION 0.8
#include <winsock2.h>
#include <stdio.h>
#include <string.h>

#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMProcessing.h"
#include "XPWidgets.h"
#include "XPStandardWidgets.h"
#include "XPLMMenus.h"

#include "TCPDataLink.h"
#include "MAVLink.h"
#include "DataRef.h"
#include "XPObject.h"
#include "XPWindow.h"
#include "XPCheckButton.h"
#include "XPTextField.h"
#include "XPLabel.h"
#include "SettingsWindow.h"

XPLMWindowID gWindow;

/* XPlane datarefs, inside a custom container */
DataRef elevator("sim/joystick/yoke_pitch_ratio");
DataRef aileron("sim/joystick/yoke_roll_ratio");
DataRef rudder("sim/joystick/yoke_heading_ratio");
DataRef throttle("sim/flightmodel/engine/ENGN_thro_use");
DataRef latitude("sim/flightmodel/position/latitude");
DataRef longitude("sim/flightmodel/position/longitude");
DataRef altitude("sim/flightmodel/position/elevation");
DataRef airspeed("sim/flightmodel/position/indicated_airspeed");
DataRef track("sim/flightmodel/position/hpath");
DataRef groundspeed("sim/flightmodel/position/groundspeed");
DataRef verticalspeed("sim/flightmodel/position/vh_ind");
DataRef phi("sim/flightmodel/position/phi");
DataRef theta("sim/flightmodel/position/theta");
DataRef psi("sim/flightmodel/position/magpsi");
DataRef P("sim/flightmodel/position/P");
DataRef Q("sim/flightmodel/position/Q");
DataRef R("sim/flightmodel/position/R");
DataRef joystickOverride("sim/operation/override/override_joystick");
DataRef throttleOverride("sim/operation/override/override_throttles");

/* Settings window for user specified parameters (IP address, etc...) */
SettingsWindow *w = new SettingsWindow();


/* Some status messages */
char controls[128];
char attitude[128];
char attitudeRates[128];
char position[128];
char velocity[128];
char status[128];

/* DataLink and MAVLink instances */
TCPDataLink *link;
MAVLink *myMAV;
bool connected = false;

/* If someone else wants control, give it */
void externalControl(bool flag) {
	joystickOverride.setInt(flag);
	throttleOverride.setInt(flag);
}

/* Set up our custom datarefs to interface nicely with MAVLink */
bool setUpDataRefs() {
	/* Configure controls to be in the -10000 to 10000 range */
	/* yoke/pedals are -1 to +1, throttle is 0 to 1 */
	elevator.setMultiplier(10000.0);
	aileron.setMultiplier(10000.0);
	rudder.setMultiplier(10000.0);
	throttle.setMultiplier(10000.0);

	/* Angles/rates in to degrees */
	phi.setMultiplier(PI/180.0);
	theta.setMultiplier(PI/180.0);
	psi.setMultiplier(PI/180.0);
	P.setMultiplier(PI/180.0);
	Q.setMultiplier(PI/180.0);
	R.setMultiplier(PI/180.0);

	airspeed.setMultiplier(0.5144);

	return true;
}

/* Callback for custom menus
 *	2nd item (listed first?!) is just a simple "About" giving some contact info
 *	1st item is a call to open the SettingsWindow
 */
void menuCallback(void *inMenuRef, void *inItemRef) {
	if (inItemRef == (void*)+2) {
		/* About window */
		char about1[256];
		sprintf(about1,"X-Plane MAVLink interface %f written by Owen McAree of LUCAS", VERSION);
		const char * about2 = "Contact: o.mcaree@lucasresearch.co.uk";


		XPWindow *aboutWindow = new XPWindow("About LUCAS MAVLink Interface",500,500,380,80);
		aboutWindow->setClosable(true);
		aboutWindow->setVisible(true);
		XPLabel *aboutLabel1 = new XPLabel(aboutWindow,about1,10,35,180,20);
		aboutLabel1->setVisible(true);
		XPLabel *aboutLabel2 = new XPLabel(aboutWindow,about2,10,15,180,20);
		aboutLabel2->setVisible(true);
	} else if (inItemRef == (void*)+1){
		/* Open SettingsWindow */
		w->open();
	}
}

/* This function is called when the SettingsWindow is closed
 *	SettingsWindow error checks all the parameters and won't let the user
 *	close the window until they are coherent, so no error checking needed
 *	here.
 *	The 'flags' are:
 *		- No Connection Specified
 *		- TCP Connection Specified
 *		- Serial Connection Specified (not supported as of v0.8)
 *	Return values means nothing (required to be an int by the callback system)
 *	
 */
int connectCallback(SettingsWindow *w) {
	
	/* If the user wants a serial connection, appologise! */
	if (w->getFlag() == 2) {
		w->error("Sorry, Serial communication currently not supported!");
		return 0; //exit immediately so we don't disconnect a current connection
	}

	/* Disconnect any links currently active */
	sprintf(status,"Not connected");
	if (link != NULL) {
		connected = false;
		link->disconnect();
		delete link;	//properly destroy the link, just to be sure
		link = NULL;
	}

	/* If user doesn't want a link, don't give them one! */
	if (w->getFlag() == 0) {
	}

	/* If the user wants a TCP link, try to create one */
	if (w->getFlag() == 1) {
		/* Get the IP */
		char ip[128];
		sprintf(ip,"%s",w->getIP());

		/* Create link and try to connected */
		link = new TCPDataLink(ip,w->getPort(), false);
		connected = link->connect();

		/* Give the user some (vaguely) useful message */
		if (connected) {
			sprintf(status,"Connected to %s:%d",ip,w->getPort());
		} else {
			sprintf(status,"No Connection to %s:%d",ip,w->getPort());
		}
	}

	/* Reinitialise MAVLink with the new DataLink */
	myMAV = new MAVLink(255,0,link);
	myMAV->setTargetComponent(1,1);

	return 0;
}

/* Quick and dirty menu creation */
/* TODO: Class-ify this */
bool setUpMenu() {
	int l = XPLMAppendMenuItem (XPLMFindPluginsMenu(),"LUCAS",NULL,1);
	XPLMMenuID lucas = XPLMCreateMenu("LUCAS",XPLMFindPluginsMenu(),l,NULL,NULL);
	int m = XPLMAppendMenuItem (lucas,"MAVLink",NULL,1);
	XPLMMenuID mavlink = XPLMCreateMenu("MAVLink",lucas,m,menuCallback,NULL);
	int settings = XPLMAppendMenuItem(mavlink,"Settings",(void*)+1,1);
	int about = XPLMAppendMenuItem(mavlink,"About",(void*)+2,1);
	return true;
}

/* Quick and dirty callback to draw the status displays */
/* TODO: Class-ify this*/
void MyDrawWindowCallback(XPLMWindowID inWindowID, void *inRefcon) {
	int	left, top, right, bottom;		//some coordinates
	int line = 12;						//height of a line
	float white[] = { 1.0, 1.0, 1.0 };	//RGB white
	float green[] = { 0.0, 1.0, 0.0 };	//RGB green
	float red[] = { 1.0, 0.2, 0.2 };	//RGB red
	
	//get the coordinates
	XPLMGetWindowGeometry(inWindowID, &left, &top, &right, &bottom);
	
	//draw a box
	XPLMDrawTranslucentDarkBox(left, top, right, top-2*line-6);

	//print the connection status
	XPLMDrawString(white, left + 5, top - line, (char*)("MAVLink Status"), NULL, xplmFont_Basic);
	if (connected) {
		XPLMDrawString(green, left + 10, top - 2*line, (char*)(status), NULL, xplmFont_Basic);
	} else {
		XPLMDrawString(red, left + 10, top - 2*line, (char*)(status), NULL, xplmFont_Basic);
	}

	//draw a box and print the outputs
	XPLMDrawTranslucentDarkBox(left, top-3*line, right, top-8*line-6);
	XPLMDrawString(white, left + 5, top - 4*line, (char*)("MAVLink HIL Outputs"), NULL, xplmFont_Basic);
	XPLMDrawString(green, left + 10, top - 5*line, (char*)(position), NULL, xplmFont_Basic);	
	XPLMDrawString(green, left + 10, top - 6*line, (char*)(velocity), NULL, xplmFont_Basic);	
	XPLMDrawString(green, left + 10, top - 7*line, (char*)(attitude), NULL, xplmFont_Basic);
	XPLMDrawString(green, left + 10, top - 8*line, (char*)(attitudeRates), NULL, xplmFont_Basic);

	//draw a box and print the inputs
	XPLMDrawTranslucentDarkBox(left, top-9*line, right, top-11*line-5);
	XPLMDrawString(white, left + 5, top - 10*line, (char*)("MAVLink HIL Inputs"), NULL, xplmFont_Basic);
	if (connected) {
		XPLMDrawString(green, left + 10, top - 11*line, (char*)(controls), NULL, xplmFont_Basic);
	} else {
		XPLMDrawString(red, left + 10, top - 11*line, (char*)("No connection"), NULL, xplmFont_Basic);
	}
}                                   

/* Flight loop callback to actually do the control
 *	Prints parameters to the status strings
 *	Determines if external control is being issues based on whether or not 
 *	we're connected to anything, and if we're not then return early (don't try
 *	receiving from MAVLink if there's no active connection!)
 *	If we have a connection, send the attitude and get the control signal
 *	Returns -1.0 to tell XPlane we want to be called on the next loop iteration
 */
float MyFlightloopCallback(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void * inRefcon) {
	int16_t s1,s2,s3,s4,s5,s6,s7,s8;
	uint8_t rssi;

	//Write status strings
	sprintf(position,"Position: %f %f", latitude.getDouble(), longitude.getDouble());
	sprintf(velocity, "IAS: %-4.1fm/s Hdg: %03.0f Trk: %03.0f", airspeed.getFloat(), psi.getFloat()*180/PI, track.getFloat());
	sprintf(attitude, "phi: %-5.2f theta: %-5.2f psi %-5.2f",phi.getFloat(), theta.getFloat(), psi.getFloat());
	sprintf(attitudeRates, "P: %-5.2f Q: %-5.2f R: %-5.2f",P.getFloat(), Q.getFloat(), R.getFloat());
	
	//Is anythign connected? If so, give it control
	externalControl(connected);

	//If not, leave...
	if (!connected) {
		return -1.0;
	}

	//If we're connected, get a message and send a couple
	int m = myMAV->receiveMessage();
	myMAV->sendAttitude(phi.getFloat(),theta.getFloat(),psi.getFloat(),P.getFloat(),Q.getFloat(),R.getFloat());
	myMAV->sendRawGPS(3,latitude.getDouble(),longitude.getDouble(),altitude.getFloat(),0,0,groundspeed.getFloat(),track.getFloat());
	myMAV->sendVFRHUD(airspeed.getFloat(),groundspeed.getFloat(),psi.getFloat()*180/PI,throttle.getFloat(0),altitude.getFloat(),verticalspeed.getFloat());
	
	//get the servo positions
	long t = myMAV->getScaledServos(s1,s2,s3,s4,s5,s6,s7,s8,rssi);
	sprintf(controls,"A:%-4.0f E:%-4.0f T:%-4.0f R:%-4.0f",(s1/100.0),(s2/100.0),(50.0+s3/200.0),(s4/100.0));

	//Set the control positions
	aileron.setFloat(s1);
	elevator.setFloat(s2);
	throttle.setFloat(0,s3);
	rudder.setFloat(s4);

	//Call us on the next loop please...
	return -1.0;
}

/* Initialise a panel to display status info in the top left */
bool setUpStatusPanel() {
	int width, height;
	XPLMGetScreenSize(&width,&height);
	gWindow = XPLMCreateWindow(20, height-20, 240, height-160, 1, MyDrawWindowCallback, NULL, NULL, NULL);
	return true;
}

/* XPlane plugin entry point
 *	Tell XPlane who we are and initialise some things
 */
PLUGIN_API int XPluginStart(char *outName, char *outSig, char *outDesc) {
	/* Who are we */
	strcpy(outName, "MAVLink");
	strcpy(outSig, "lucas.plugins.mavlink");
	strcpy(outDesc, "This plugin outputs MAVLink compatible messages");

	//set up some things
	setUpStatusPanel();
	setUpMenu();
	setUpDataRefs();

	//tell our SettingsWindow what to call on close
	w->setSaveCallback(connectCallback);

	//call it now to connect if a saved connection exists
	connectCallback(w);

	//regiaster our flight loop callback
	XPLMRegisterFlightLoopCallback(MyFlightloopCallback,-1.0, NULL);
	

	return 1;
}

/* when we're stopped, disconnect and destroy our status window
 * TODO: do a bit more housekeeping here!
 */
PLUGIN_API void	XPluginStop(void) {
	if (link != NULL) {
		link->disconnect();
	}
	XPLMDestroyWindow(gWindow);
}

/* When we're disabled, give the user back control */
PLUGIN_API void XPluginDisable(void) {
	externalControl(false);
}

/* When we're enabled, take control back if we can */
PLUGIN_API int XPluginEnable(void) {
	externalControl(connected);
	return 1;
}

//Do nothing with this method, but we have to have it!
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFromWho, long inMessage, void *inParam) {}
