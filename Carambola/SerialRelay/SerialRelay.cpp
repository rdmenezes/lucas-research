#include "SerialRelay.h"

SerialRelay::SerialRelay() : SerialDataLink(SERIAL_PORT, SERIAL_BAUD) {
	SerialDataLink::connect();
	myMAVLink = new MAVLink(1,2,this);
}

void SerialRelay::run() {
	char buf[SERIAL_BUFFER];
	int i = 0;
	printf("Running...\n");
	while (true) {
		int chars = SerialDataLink::receive(SERIAL_BUFFER, buf);
		for (int j = 0; j < chars; j++) {
			printf("%d - %d/%d - 0x%X\n", i, j, chars, (unsigned char)buf[j]);
		}
		i++;
		usleep(1);
	}
}


int main() {
	SerialRelay *myRelay = new SerialRelay();
	myRelay->run();
}
