/*
 *			Joystick class for Linux
 * Interfaces with a joystick to provide axis and button data
 * to an application. Utilises threading to sample joystick events
 * in the background.
 *
 */

#ifndef Joystick_h
#define Joystick_h

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#include "Thread.h"

class Joystick : public Thread {
public:
	Joystick(const char * device);
	~Joystick();
	float getAxis(int index);
	bool getButton(int index);
	int numberOfAxis();
	int numberOfButtons();
	
protected:
	void threadedFunction();

private:
	bool openJoystick();
	bool getJoystickDetails();
	bool readJoystick();
	bool closeJoystick();

	const char * device;
	int joystick_fd, *axis, num_of_axis, num_of_buttons;
	char *button, name_of_joystick[80];
};
#endif
