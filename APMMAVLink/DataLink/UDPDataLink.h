/* Specialisation of the DataLink interface for the User Datagram Protocol (UDP)
 *
 * Implements the Windows Sockets (winsock2) library to open a UDP socket to
 * send and receive a character array.
 */

#ifndef UDPDataLink_h
#define UDPDataLink_h

#ifdef _WIN32
	#include <winsock2.h>
	#pragma comment(lib, "Ws2_32.lib")
#elif __linux__
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <netinet/in.h>
	#include <sys/ioctl.h>
	#include <iostream>
	#include <errno.h>
#endif

#include <stdio.h>
#include "DataLink.h"



#ifdef _WIN32
	class __declspec( dllexport ) UDPDataLink : public DataLink {
#else
	class UDPDataLink : public DataLink {
#endif
public:
	UDPDataLink(const char * address, int port);
	~UDPDataLink();
	bool connect();
	bool send(char * message, int bytes);
	int receive(int bytes, char * message);
	void setReceiveTimeout(int timeout);
	bool setReceiveBuffer(int bytes);
	bool disconnect();

private:
	bool startWindowsSockets();
	bool setupLocalInterface(int port);
	bool setupDestinationAddress(const char * address, int port);
	bool createSocket();
	bool bindSocket();
	bool setReuseAddress(bool flag);
	
	bool socketDataAvailable();
	int receivePacket(int bytes, char * message);
	const char * address;
	int port;
	int timeout;
	struct sockaddr_in local, destination;
#ifdef _WIN32
	SOCKET udpSocket;
#elif __linux__
	int udpSocket;
#endif
};

#endif
