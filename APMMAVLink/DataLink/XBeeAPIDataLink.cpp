#include "XBeeAPIDataLink.h"

std::map<std::string, std::list<XBeeAPIReceivePacket>> XBeeAPIDataLink::PacketCache;


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

	receive();

	char myKey[36];
	sprintf(myKey,"0x%X 0x%X",addressUpper, addressLower);

	if (PacketCache.find(myKey) != PacketCache.end()) {
		int l = 0;
		while (l <= bytes && !PacketCache[myKey].empty()) {
			memcpy(message + l,PacketCache[myKey].front().data,PacketCache[myKey].front().length - 12);
			l += PacketCache[myKey].front().length - 12;
			PacketCache[myKey].pop_front();
		}
		return l;
	}
	return 0;






/*	unsigned char packet[XBEE_API_PACKET_LENGTH];

	//call the overridden function
	char myKey[36];
		
	int length = 0;

	if (PacketCache.find(myKey) != PacketCache.end()) {
	//	printf("Cached...\n");
		length = PacketCache[myKey].length - 12;
		memcpy(message,PacketCache[myKey].data, length);
		PacketCache.erase(myKey);
		return length;
	}


//	printf("\n");
	if (PacketCache.find(myKey) != PacketCache.end()) {
		length = PacketCache[myKey].length - 12;
		memcpy(message,PacketCache[myKey].data,length);
		PacketCache.erase(myKey);
		return length;
	} else {
		return -1;
	}

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
//		printf("%d\n", l);
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
		int length = packetLength-16;
		memcpy(message,packet+15,length);
		return length;
	}
	return -1;*/
}


bool XBeeAPIDataLink::receive() {
	XBeeAPIReceivePacket myPacket;
	parsedBytes = 0;
	parsedChecksum = 0xFF;
	int l = 0, l2 = 0;
	char b;
	do {
		l = SerialDataLink::receive(1, &b);
		l2 += l;
//		if (l <= 0) {
//			Sleep(1);
//		}
//		printf("0x%X ", (unsigned char)b);
	} while (l > 0 && l2 < 110 && !parseAPIFrame(b,&myPacket));

	char key[36];
	sprintf(key,"0x%X 0x%X",myPacket.addressUpper, myPacket.addressLower);
	PacketCache[key].push_back(myPacket);
//	printf("\n--0x%X 0x%X\n",myPacket.addressUpper, myPacket.addressLower);
	return true;
}



bool XBeeAPIDataLink::parseAPIFrame(unsigned char c, XBeeAPIReceivePacket *myFrame) {
	//If we don't have a packet started and we don't see start character, ignore it
	if (parsedBytes == 0 && c != 0x7E) {
		return false;
	}
//	printf("(%d,0x%X) ",parsedBytes, c);
	if (parsedBytes == 0 && c == 0x7E) {
		parsedBytes = 1;
		parsedChecksum = 0xFF;
		myFrame->addressUpper = 0;
		myFrame->addressLower = 0;
		myFrame->shortAddress = 0;
		myFrame->receiveOptions = 0;
		memset(myFrame->data,'\0', 84);
		return false;
	}
	switch (parsedBytes) {
	case 1:
		myFrame->length = c << 8;
		parsedBytes++;
		return false;
	case 2:
		myFrame->length = myFrame->length + c;
		parsedBytes++;
//		printf("[l = %d] ",myFrame->length+3);
		return false;
	case 3:
		if (c != 0x90) {
			parsedBytes = 0;
			parsedChecksum = 0xFF;
			printf("Packet 0x%X received\n", c);
		} else {
			parsedBytes++;
			parsedChecksum -= c;
		}
		return false;
	case 4:
		myFrame->addressUpper = c << (3 * 8);
		parsedBytes++;
		parsedChecksum -= c;
		return false;
	case 5:
		myFrame->addressUpper = myFrame->addressUpper + (c << (2 * 8));
		parsedBytes++;
		parsedChecksum -= c;
		return false;
	case 6:
		myFrame->addressUpper = myFrame->addressUpper + (c << (1 * 8));
		parsedBytes++;
		parsedChecksum -= c;
		return false;
	case 7:
		myFrame->addressUpper = myFrame->addressUpper + c;
		parsedBytes++;
		parsedChecksum -= c;
		return false;
	case 8:
		myFrame->addressLower = c << (3 * 8);
		parsedBytes++;
		parsedChecksum -= c;
		return false;
	case 9:
		myFrame->addressLower = myFrame->addressLower + (c << (2 * 8));
		parsedBytes++;
		parsedChecksum -= c;
		return false;
	case 10:
		myFrame->addressLower = myFrame->addressLower + (c << (1 * 8));
		parsedBytes++;
		parsedChecksum -= c;
		return false;
	case 11:
		myFrame->addressLower = myFrame->addressLower + c;
		parsedBytes++;
		parsedChecksum -= c;
		return false;
	case 12:
		myFrame->shortAddress = c << 8;
		parsedBytes++;
		parsedChecksum -= c;
		return false;
	case 13:
		myFrame->shortAddress = myFrame->shortAddress + c;
		parsedBytes++;
		parsedChecksum -= c;
		return false;
	case 14:
		myFrame->receiveOptions = c;
		parsedBytes++;
		parsedChecksum -= c;
		return false;
	}
	if (parsedBytes < (myFrame->length + 3)) {
		myFrame->data[parsedBytes-15] = c;
		parsedBytes++;
		parsedChecksum -= c;
		return false;
	}
	if (parsedBytes == (myFrame->length + 3)) {
		if (parsedChecksum == c) {
			myFrame->checksum = parsedChecksum;
			parsedBytes = 0;
			parsedChecksum = 0xFF;
			return true;
		} else {
			printf("\n\nChecksum Error! 0x%X\n", parsedChecksum);
			parsedBytes = 0;
			parsedChecksum = 0xFF;
			return false;
		}
	} 
}