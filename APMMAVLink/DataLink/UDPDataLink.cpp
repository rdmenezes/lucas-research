#include "UDPDataLink.h"

/* Constrctor for the UDPDataLink class.
 *	Sets up the address and port instance variables
 */
UDPDataLink::UDPDataLink(const char * address, int port) {
	this->address = address;
	this->port = port;
	timeout = 1000;
	sprintf(ident,"%s:%d", address, port);
	sprintf(type,"UDP");
}

/* Destrctor for the UDPDataLink class.
 *	Disconnects the sockt
 */
UDPDataLink::~UDPDataLink() {
	disconnect();
}

/* Connect function to initialise the UDP socket
 *	Returns true if sockt created successfully, false otherwise
 */
bool UDPDataLink::connect() {
	return	startWindowsSockets() &&					//start winsock
			setupLocalInterface(port) &&				//set up local interface
			setupDestinationAddress(address, port) &&	//set up desination address
			createSocket() &&							//create socket
			setReuseAddress(true) &&					//enable address reuse
			bindSocket();								//bind socket
}

/* Send function
 *	Takes the message as a char array and its length as an integer
 *	Returns true if the message was successfully sent (but no gaurentees it was received)
 *	false otherwise
 */
bool UDPDataLink::send(char * message, int bytes) {
	int result = sendto(udpSocket, message, bytes, 0, (sockaddr *) &destination, sizeof(destination));
#ifdef _WIN32
	if (result == SOCKET_ERROR) {
		fprintf(stderr, "UDPDataLink failed to send. Error %d\n", WSAGetLastError());
		return false;
	}
#elif __linux__
	if (result == -1) {
		fprintf(stderr,"UDPDataLink failed to send. Error %d\n", errno);
	}
#endif
	return true;
}

/* Receive function 
 *	Takes the (maximum) length of message to be received and a pointer to the char array
 *	to be returned
 *	Returns the actual number of bytes received
 */
int UDPDataLink::receive(int bytes, char * message) {
	if (socketDataAvailable()) {				//check for a timeout
		return receivePacket(bytes, message);
	}
	return -1;
}

/* Set the receive timeout
 * Takes the timeout in milliseconds as an integer, returns nothing
 */
void UDPDataLink::setReceiveTimeout(int timeout) {
	this->timeout = timeout;
}

/* Set the size of the receive buffer in bytes
 * Take an integer number of bytes
 * Returns true if successfully set, false otherwise
 */
bool UDPDataLink::setReceiveBuffer(int bytes) {
	int bufSize = bytes*8;
	int result = setsockopt(udpSocket, SOL_SOCKET, SO_RCVBUF, (char *)&bufSize, (int)sizeof(bufSize));
#ifdef _WIN32	
	if (result == SOCKET_ERROR) {
		fprintf(stderr, "Unable to set RCVBUF option in UDPDataStream. Error %d\n", WSAGetLastError());
		return false;
	}
#elif __linux__
	if (result == -1) {
		fprintf(stderr,"Unable to set RCVBUF option in UDPDataStream. Error %d\n", errno);
	}
#endif
	return true;
}


/* Disconnect function, closes soket and cleans up winsock
 *	Returns true if all goes well
 */
bool UDPDataLink::disconnect() {
#ifdef _WIN32
	int result = closesocket(udpSocket);
	if (result == SOCKET_ERROR) {
		fprintf(stderr, "Unable to close socket in udpDataLink. Error %d\n", WSAGetLastError());
		return false;
	}
	WSACleanup();
#elif __linux__
	close(udpSocket);
#endif
	return true;
}

/* Start the Windows sockets
 *	Returns true on success
 */
bool UDPDataLink::startWindowsSockets() {
#ifdef _WIN32
	WSAData socketData;
	int result = WSAStartup(MAKEWORD(2,2), &socketData);
	if (result != NO_ERROR) {
		fprintf(stderr, "Error at WSAStartup() in UDPDataLink\n");
		return false;
	}
#endif
	return true;
}

/* Set up the address structure for the local interface
 * Allowing connections from any IP on he specified port
 */
bool UDPDataLink::setupLocalInterface(int port) {
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	local.sin_port = htons(port);
	return true;
}

/* Set up the address structure for the detination address */
bool UDPDataLink::setupDestinationAddress(const char * address, int port) {
	destination.sin_family = AF_INET;
	destination.sin_addr.s_addr = inet_addr(address);
	destination.sin_port = htons(port);
	return true;
}

/* Create the socket */
bool UDPDataLink::createSocket() {
	udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
#ifdef _WIN32
	if (udpSocket == INVALID_SOCKET) {
		fprintf(stderr, "Socket initialisation failed in UDPDataStream. Error %d\n", WSAGetLastError());
		return false;
	}
#elif __linux__
	if (udpSocket == -1) {
		fprintf(stderr,"Socket initialisation failed in UDPDataStream. Error %d\n", errno);
	}
#endif
	return true;
}

/* Bind the socket to the port */
bool UDPDataLink::bindSocket() {
	int result = bind(udpSocket, (sockaddr *)&local, sizeof(local));
#ifdef _WIN32
	if (result == SOCKET_ERROR) {
		fprintf(stderr, "Unable to bind to port %d in UDPDataStream. Error %d\n", port, WSAGetLastError());
		return false;
	}
#elif __linux__
	if (result == -1) {
		fprintf(stderr,"Unable to bind to port %d in UDPDataStream. Error %d\n", port, errno);
	}
#endif
	return true;
}

/* Function to enable port reuse (enable the SO_REUSEADDR option)
*	In theory this should allow server and client to reside on the same machine (bound to the
*	same port utilising the loopback interface (127.0.0.1), without requiring specialised
*	client/server instances. However this is totaly untested...
*	TODO: Test loopback implementation
*	Takes a boolean flag to indicate enabled/disables
*	Returns true if set successfully and false otherwise
*/
bool UDPDataLink::setReuseAddress(bool flag) {
	char optval = (char)flag;
	int result = setsockopt(udpSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
#ifdef _WIN32
	if (result == SOCKET_ERROR) {
		fprintf(stderr, "Unable to set REUSEADDR option in UDPDataStream. Error %d\n", WSAGetLastError());
		return false;
	}
#elif __linux__
	if (result == -1) {
		//This appears not to work at all on linux, so ignore the error for now!
		//fprintf(stderr,"Unable to set REUSEADDR option in UDPDataStream. Error %d\n", errno);
	}
#endif
	return true;
}

/* Test to see if data is available on the socket within the specified timeout
 *	Returns true if data available, false if timeout is reached
 */
bool UDPDataLink::socketDataAvailable() {
	struct timeval socketTimeout;
	fd_set socketRead;

	socketTimeout.tv_sec = 0;
	socketTimeout.tv_usec = timeout*1000;
	FD_ZERO(&socketRead);
	FD_SET(udpSocket, &socketRead);

	int b = select(udpSocket+1, &socketRead, 0, 0, &socketTimeout);

	if (b <= 0) {
//        	printf("No reply!\n");
		return false;
    	}
	if (FD_ISSET(udpSocket, &socketRead)) {
		return true;
	}
	return false;
}

/* Receive a packet, assuming data is available (i.e. will block)
 *	Takes an integer representing the maximum number of bytes to read and a pointer
 *	to the char array to return
 *	Returns the actual number of bytes read
 */
int UDPDataLink::receivePacket(int bytes, char * message) {
	sockaddr_in sockDat;
	int addrLength = sizeof(sockDat);
#ifdef _WIN32
	int result = recvfrom(udpSocket, message, bytes, 0, (sockaddr *) &sockDat, &addrLength);
	if (result == SOCKET_ERROR) {
		fprintf(stderr, "UDPDataLink failed to receive. Error %d\n", WSAGetLastError());
		return -1;
	}
#elif __linux__
	int result = recvfrom(udpSocket, message, bytes, 0, (sockaddr *) &sockDat, (socklen_t*)&addrLength);
	if (result == -1) {
		fprintf(stderr,"UDPDataLink failed to receive. Error %d\n", errno);
	}
#endif
	return result;
}
