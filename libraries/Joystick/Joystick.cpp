#include "Joystick.h"

//Constructor
Joystick::Joystick(const char * device) : Thread() {
	this->device = device;
	this->num_of_axis = 0;
	this->num_of_buttons = 0;
	openJoystick();		//Open the joystick file
	getJoystickDetails();	//Get its details
	Thread::start();	//Start the thread
}

//Destructor
Joystick::~Joystick() {
	Thread::stop();		//Stop the thread
	closeJoystick();	//Close joystick file
}

//Getters
float Joystick::getAxis(int index) {
	return axis[index] / 32767.0f;	//Return scaled (-1 to 1) axis
}
bool Joystick::getButton(int index) {
	return (bool)button[index];	//Return logical button
}
int Joystick::numberOfAxis() {
	return num_of_axis;		//Return number of axis
}
int Joystick::numberOfButtons() {
	return num_of_buttons;		//Return number of buttons
}

//Private functions
//Open the joystick file, with error checking
//Returns true on success, False (with stderr message) otherwise
bool Joystick::openJoystick() {
	if((joystick_fd = open(device, O_RDONLY)) == -1 ) {
		fprintf(stderr, "Couldn't open joystick %s\n", device);
		return false;
	}
	return true;
}

//Get the joystick details. Number of axis/buttons and name
//Returns false if there are no buttons or axis, otherwise true
bool Joystick::getJoystickDetails() {
	//interrogate joystick
	ioctl(joystick_fd, JSIOCGAXES, &num_of_axis );
	ioctl(joystick_fd, JSIOCGBUTTONS, &num_of_buttons );
	ioctl(joystick_fd, JSIOCGNAME(80), &name_of_joystick );

	//test for axis/buttons
	if (num_of_axis == 0 && num_of_buttons == 0) {
		fprintf(stderr, "Joystick has no axis or buttons!\n");
		return false;
	}

	//allocate memory for axis/buttons
	axis = (int *) calloc( num_of_axis, sizeof( int ) );
	button = (char *) calloc( num_of_buttons, sizeof( char ) );

	//set non-blocking mode (for threaded reading)
	fcntl(joystick_fd, F_SETFL, O_NONBLOCK );

	return true;
}

//Read the latest joystick event, decode it in to axis
//or button arrays
bool Joystick::readJoystick() {
	struct js_event js;
	read(joystick_fd, &js, sizeof(struct js_event));
	switch (js.type & ~JS_EVENT_INIT) {
		case JS_EVENT_AXIS:
			axis[js.number] = js.value;
			break;
		case JS_EVENT_BUTTON:
			button[js.number] = js.value;
			break;
	}
}

//Close the joystick file
bool Joystick::closeJoystick() {
	close(joystick_fd);
}

//Threaded function (called by Thread superclass) to periodically
//sample joystick
void Joystick::threadedFunction() {
	//read the joystick
	readJoystick();

	//sleep to maintain at least 100Hz, assuming all events fire
	usleep(10000/(num_of_axis + num_of_buttons));
}


//Test code
/*int main() {
	Joystick *myStick = new Joystick("/dev/input/js1");
	while (true) {
		for (int i = 0; i<myStick->numberOfAxis(); i++) {
			printf("%.2f\t", myStick->getAxis(i));
		}
//		for (int i = 0; i<myStick->numberOfButtons(); i++) {
//			printf("%d\t", myStick->getButton(i));
//		}
		printf("\n");
		usleep(10000);
	}
}*/
