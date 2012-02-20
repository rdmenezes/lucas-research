#include "XBeeAPIDataLink.h"

/* Constructors */
XBeeAPIDataLink::XBeeAPIDataLink(const char * comPort, int baudRate, unsigned long upper, unsigned long lower) :
SerialDataLink(comPort,baudRate) {
	SerialDataLink::setNumberOfStopBits(TWOSTOPBITS);
	this->addressUpper = upper;
	this->addressLower = lower;
	this->shortAddress = 0xFFFE;
	this->checkForShort = true;
};

XBeeAPIDataLink::XBeeAPIDataLink(SerialDataLink &dl, unsigned long upper, unsigned long lower) :
SerialDataLink(dl) {
	SerialDataLink::setNumberOfStopBits(TWOSTOPBITS);
	this->addressUpper = upper;
	this->addressLower = lower;
	this->shortAddress = 0xFFFE;
	this->checkForShort = true;
};

/* Send function
 *	Overloads the SerialDataLink implementation to wrap the data
 *	in an API packet, then calls the SerialDataLink send routine
 */
bool XBeeAPIDataLink::send(char * message, int bytes) {
	//how long is the packet going to be?
	//(minus 4 bytes, as per the API)
	unsigned short length = bytes + 14;

	//buffer for the packet
	unsigned char packet[XBEE_API_PACKET_LENGTH];

	packet[0] = 0x7E;	//start character

	//packet length (note XBee uses reversed byte orders)
	*(short*)(packet+1) = _byteswap_ushort(length);


	packet[3] = 0x10;	//packet type (transmit)
	
	//do we want an acknowledgement packet
	//yes if we want to know the 16-bit address
	//no generally
	packet[4] = checkForShort;

	//64-bit address (revered bytes)
	*(long*)(packet+5) = _byteswap_ulong(addressUpper);
	*(long*)(packet+9) = _byteswap_ulong(addressLower);

	//16-bit address if known (reversed bytes)
	*(short*)(packet+13) = _byteswap_ushort(shortAddress);

	packet[15] = 0x00;	//broadcast radius (max)
	packet[16] = 0x00;	//options (none)
	
	//copy in the actual data we want to send
	//no checks to see if buffer is big enough
	//TODO: see above...
	memcpy(packet+17,message,bytes);
	
	//calculate checksum as per API
	unsigned char chksum = 0;
	for (int i = 0; i<length; i++) {
		chksum += packet[i+3];
	}
	packet[length+3] = 0xFF-chksum;

	//send the data by calling the overridden function
	if (SerialDataLink::send((char*)packet,length+4)) {
		if (checkForShort) {
			//if the data sent and we want a reply, check for one
			int l = SerialDataLink::receive(XBEE_API_PACKET_LENGTH, (char*)packet);
			//if we get an acknowledge packet, read the address then stop checking
			if (packet[3] == 0x8B) {
				shortAddress = _byteswap_ushort(*(short*)(packet+5));
				checkForShort = false;
			}
		}
		//everything went well
		return true;
	}
	//or it didn't
	return false;
}

/* Receive Function
 *	Overrides the SerialDataLink receive, calls it then strips off
 *	the XBee stuff
 */
int XBeeAPIDataLink::receive(int bytes, char * message) {
	//buffer
	unsigned char packet[XBEE_API_PACKET_LENGTH];

	//call the overridden function
	int l = SerialDataLink::receive(XBEE_API_PACKET_LENGTH, (char*)(packet));

//	printf("%d\n", l);
//	for (int i = 0; i<l; i++) {
///		printf("0x%X ", packet[i]);
//	}	
//	printf("\n");

	//if the packet isn't big enough to make sense of (can't read its length)
	//or doesn't start with the right character, exit immediately
	if (l <= 3 || packet[0] != 0x7E) {return 0;}

	//how long should the packet be?
	short packetLength = _byteswap_ushort(*(short*)(packet+1)) + 4;
	
	//how long is the packet?
	int currentLength = l;

//	printf ("%d \n", packetLength);

	int counter = 0;
	//while the packet is too small, make it bigger
	while (currentLength < packetLength) {
		l = SerialDataLink::receive(XBEE_API_PACKET_LENGTH-currentLength, (char*)(packet+currentLength));
		if (l == 0) {
			counter++;
			if (counter > 10) { return 0;}
		}
		currentLength += l;
		//printf("%d\n", l);
//		for (int i = 0; i<currentLength; i++) {
//			printf("0x%X ", packet[i]);
//		}	
//		printf("\n");
	}
//	printf("------------------------------------\n");
	//(if we overread, the data gets discarded)
	//TODO: buffer this data

	//if we've received data from somewhere (not random status information)
	//return the data to the caller
	if (packet[3] == 0x90) {
		int length = packetLength;
		memcpy(message,packet+15,length);
		return length;
	}
	return -1;
}