#include "SerialDataLink.h"


SerialDataLink::SerialDataLink(const char * comPort, int baudRate) {
	this->comPort = comPort;
	this->baudRate = checkBaudRate(baudRate);
	this->byteSize = 8;
#ifdef _WIN32
	this->stopBits = ONESTOPBIT;
	this->parity = NOPARITY;
#endif
	this->connected = false;
	sprintf(ident,"%s", comPort);
	sprintf(type,"Serial");
}

bool SerialDataLink::connect() {
#ifdef _WIN32
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
#else
	hSerial = open(comPort, O_RDWR | O_NOCTTY);
	struct termios options;
	tcgetattr(hSerial, &options);

	cfsetispeed(&options, baudRate);
	cfsetospeed(&options, baudRate);

	options.c_cflag |= (CLOCAL | CREAD);
	options.c_cflag &= ~CSIZE; /* Mask the character size bits */
	options.c_cflag |= CS8;    /* Select 8 data bits */
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
     	options.c_cc[VMIN]=1;
        options.c_cc[VTIME]=0;
	tcsetattr(hSerial, TCSANOW, &options);



#endif
	connected = true;
	return true;
}

bool SerialDataLink::send(char * message, int bytes) {
	DWORD dwBytesWritten = 0;
#ifdef _WIN32
	if (WriteFile(hSerial, message, bytes, &dwBytesWritten, NULL)) {
#else
	if (dwBytesWritten = write(hSerial, message, bytes)) {
#endif
		if (dwBytesWritten == bytes) {
			return true;
		}
	} else {
#ifdef _WIN32
		fprintf(stderr, "SerialDataLink unable to send (error %d)\n",GetLastError());
#else
		fprintf(stderr, "SerialDataLink unable to send\n");
#endif
	}
	return false;
}

int SerialDataLink::receive(int bytes, char * message) {
	DWORD dwBytesRead;
#ifdef _WIN32
	if (ReadFile(hSerial, message, bytes, &dwBytesRead, NULL)) {
#else
	if (dwBytesRead = read(hSerial, message, bytes)) {
#endif
		return dwBytesRead;
	}
	return 0;
}

bool SerialDataLink::disconnect() {
#ifdef _WIN32
	if (CloseHandle(hSerial)) {
		connected = false;
		return true;
	} else {
		return false;
	}
#else
	close(hSerial);
	return true;
#endif
}

void SerialDataLink::setNumberOfStopBits(int stopBits) {
	this->stopBits = stopBits;
}

DWORD SerialDataLink::checkBaudRate(int baudRate) {
	switch (baudRate) {
	case (2400):
#ifdef _WIN32
		return CBR_2400;
#else
		return B2400;
#endif
		break;
	case (4800):
#ifdef _WIN32
		return CBR_4800;
#else
		return B4800;
#endif
		break;
	case (9600):
#ifdef _WIN32
		return CBR_9600;
#else
		return B9600;
#endif
		break;
	case (19200):
#ifdef _WIN32
		return CBR_19200;
#else
		return B19200;
#endif
		break;
	case (38400):
#ifdef _WIN32
		return CBR_38400;
#else
		return B38400;
#endif
		break;
	case (57600):
#ifdef _WIN32
		return CBR_57600;
#else
		return B57600;
#endif
		break;
	case (115200):
#ifdef _WIN32
		return CBR_115200;
#else
		return B115200;
#endif
		break;
#ifdef _WIN32
	case (256000):
		return CBR_256000;
#endif
		break;
	default:
		fprintf(stderr,"Unknown baud rate (%d) in SerialDataLink\n", baudRate);
		return NULL;
	}
}
