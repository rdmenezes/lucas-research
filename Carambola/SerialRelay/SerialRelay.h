#ifndef SerialRelay_h
#define SerialRelay_h

#include "SerialDataLink.h"
#include "MAVLink.h"

#define SERIAL_PORT "/dev/ttyS0"
#define SERIAL_BAUD 57600
#define SERIAL_BUFFER 1024


class SerialRelay : private SerialDataLink {
public:
	SerialRelay();
	void run();


private:
	MAVLink * myMAVLink;

};

#endif
