#ifndef SerialDataLink_h
#define SerialDataLink_h

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "DataLink.h"


class SerialDataLink : public DataLink {
public:
	SerialDataLink(const char * comPort, int baudRate);
	bool connect();
	bool send(char * message, int bytes);
	int receive(int bytes, char * message);
	bool disconnect();
	void setByteSize(int bits);
private:
	DWORD checkBaudRate(int baudRate);
	const char * comPort;
	DWORD baudRate;
	DWORD stopBits;
	DWORD parity;
	HANDLE hSerial;
	int byteSize;
};
#endif