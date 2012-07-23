#include "Joystick.h"

int main() {
	Joystick *myStick = new Joystick("/dev/input/js0");
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
}
