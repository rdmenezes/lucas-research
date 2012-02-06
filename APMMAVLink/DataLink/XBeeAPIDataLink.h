/* Wrapper for the SerialDataLink to deal with XBee API packets
 *	This class wraps outgoing data in addressed packets enabling
 *	the use of a XBee API Coordinator which easily handles
 *	multiple clients
 *
 *	Presently, incoming data is output regardless of its source
 *	as this fits with the static nature of the MAVLink data stores
 */

#ifndef XBeeAPIDataLink_h
#define XBeeAPIDataLink_h

#include <string.h>
#include <intrin.h>
#include "SerialDataLink.h"

#define XBEE_API_PACKET_LENGTH 1024
#ifdef _WIN32
	 class __declspec( dllexport ) XBeeAPIDataLink : public SerialDataLink {
#else 
	class XBeeAPIDataLink : public SerialDataLink {
#endif
public:
	//constructor to create a new SerialDataLink
	XBeeAPIDataLink(const char * comPort, int baudRate, unsigned long upper, unsigned long lower);

	//constructor to copy a SerialDataLink
	XBeeAPIDataLink(SerialDataLink &dl, unsigned long upper, unsigned long lower);
	
	//general datalink methods
	bool send(char * message, int bytes);
	int receive(int bytes, char * message);

	//should our class check for the sources 16-bit address
	bool checkForShortAddress(bool b);
private:
	unsigned long addressUpper, addressLower;
	short shortAddress;
	bool checkForShort;
};


#endif