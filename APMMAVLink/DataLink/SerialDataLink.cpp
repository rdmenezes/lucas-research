#include "SerialDataLink.h"


SerialDataLink::SerialDataLink(const char * comPort, int baudRate) {
	this->comPort = comPort;
	this->baudRate = checkBaudRate(baudRate);
	this->byteSize = 8;
	this->stopBits = ONESTOPBIT;
	this->parity = NOPARITY;
	this->connected = false;
	sprintf(ident,"%s", comPort);
	sprintf(type,"Serial");
}

bool SerialDataLink::connect() {
	hSerial = CreateFile(comPort,
			GENERIC_READ | GENERIC_WRITE,
			0,
			0,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			0);
	if(hSerial==INVALID_HANDLE_VALUE){
		if(GetLastError()==ERROR_FILE_NOT_FOUND){
			fprintf(stderr,"COM Port not found in SerialDataLink\n");
			return false;
		}
		fprintf(stderr,"Invalid COM Port in SerialDataLink\n");
		return false;
	}

	DCB dcbSerialParams = {0};
	DCB dcbSerial = {0};
	dcbSerial.DCBlength=sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams)) {
		fprintf(stderr,"Could not get COM Port state in SerialDataLink\n");
		return false;
	}
	dcbSerialParams.BaudRate=baudRate;
	dcbSerialParams.ByteSize=byteSize;
	dcbSerialParams.StopBits=stopBits;
	dcbSerialParams.Parity=parity;
	if(!SetCommState(hSerial, &dcbSerialParams)){
		fprintf(stderr,"Could not set COM Port state in SerialDataLink\n");
		return false;
	}
    COMMTIMEOUTS timeouts={0};
	timeouts.ReadIntervalTimeout=1;
    timeouts.ReadTotalTimeoutConstant=10;
    timeouts.ReadTotalTimeoutMultiplier=0;
    timeouts.WriteTotalTimeoutConstant=5;
    timeouts.WriteTotalTimeoutMultiplier=0;
    if(!SetCommTimeouts(hSerial, &timeouts)){
        fprintf(stderr,"Could not set timeouts in SerialDataLink\n");
		return false;
    }
	connected = true;
	return true;
}

bool SerialDataLink::send(char * message, int bytes) {
	DWORD dwBytesWritten = 0;
	if (WriteFile(hSerial, message, bytes, &dwBytesWritten, NULL)) {
		if (dwBytesWritten == bytes) {
			return true;
		}
	} else {
		fprintf(stderr, "SerialDataLink unable to send (error %d)\n",GetLastError());
	}
	return false;
}

int SerialDataLink::receive(int bytes, char * message) {
	DWORD dwBytesRead;
	if (ReadFile(hSerial, message, bytes, &dwBytesRead, NULL)) {
		return dwBytesRead;
	}
	return 0;
}

bool SerialDataLink::disconnect() {
	if (CloseHandle(hSerial)) {
		connected = false;
		return true;
	} else {
		return false;
	}
}

void SerialDataLink::setNumberOfStopBits(int stopBits) {
	this->stopBits = stopBits;
}

DWORD SerialDataLink::checkBaudRate(int baudRate) {
	switch (baudRate) {
	case (2400):
		return CBR_2400;
		break;
	case (4800):
		return CBR_4800;
		break;
	case (9600):
		return CBR_9600;
		break;
	case (19200):
		return CBR_19200;
		break;
	case (38400):
		return CBR_38400;
		break;
	case (57600):
		return CBR_57600;
		break;
	case (115200):
		return CBR_115200;
		break;
	case (256000):
		return CBR_256000;
		break;
	default:
		fprintf(stderr,"Unknown baud rate (%d) in SerialDataLink\n", baudRate);
		return NULL;
	}
}