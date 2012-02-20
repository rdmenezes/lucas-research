#include "TCPDataLink.h"

TCPDataLink::TCPDataLink(const char * address, int port, bool server) {
	this->address = address;
	this->port = port;
	timeout = 1000;
	sprintf(ident,"%s:%d", address, port);
	sprintf(type,"TCP");
	if (server) {
		fprintf(stderr, "TCP server requested in TCPDataLink, this is currently not supported!\n");
	}
}

/* Destrctor for the UDPDataLink class.
 *	Disconnects the sockt
 */
TCPDataLink::~TCPDataLink() {
	disconnect();
}

/* Connect function to initialise the UDP socket
 *	Returns true if sockt created successfully, false otherwise
 */
bool TCPDataLink::connect() {
	if (startWindowsSockets() &&
			setupLocalInterface(port) &&
			setupDestinationAddress(address, port) &&
			createSocket() &&
			setReuseAddress(true) &&
			connectAsClient()) {
		connected = true;
		return true;
	} else {
		connected = false;
		return false;
	}
	
}

/* Disconnect function, closes soket and cleans up winsock
 *	Returns true if all goes well
 */
bool TCPDataLink::disconnect() {
#ifdef _WIN32
	int result = closesocket(tcpSocket);
	if (result == SOCKET_ERROR) {
		fprintf(stderr, "Unable to close socket in TCPDataLink. Error %d\n", WSAGetLastError());
		return false;
	}
	WSACleanup();
#elif __linux__
	close(tcpSocket);
#endif
	connected = false;
	return true;
}


bool TCPDataLink::send(char * message, int bytes) {
	int result = ::send(tcpSocket, message, bytes,0);
#ifdef _WIN32
	if (result == SOCKET_ERROR) {
		printf("TCPDataLink failed to send. Error %d\n", WSAGetLastError());
		return false;
	}
#elif __linux__
	if (result == -1) {
		fprintf(stderr,"TCPDataLink failed to send. Error %d\n", errno);
	}
#endif
	return true;
}

int TCPDataLink::receive(int bytes, char * message) {
	if (socketDataAvailable()) {				//check for a timeout
		return receivePacket(bytes, message);
	}
	return -1;
}


/* Test to see if data is available on the socket within the specified timeout
 *	Returns true if data available, false if timeout is reached
 */
bool TCPDataLink::socketDataAvailable() {
	struct timeval socketTimeout;
	fd_set socketRead;

	socketTimeout.tv_sec = 0;
	socketTimeout.tv_usec = timeout*1000;
	FD_ZERO(&socketRead);
	FD_SET(tcpSocket, &socketRead);

	int b = select(tcpSocket+1, &socketRead, 0, 0, &socketTimeout);

	if (b == 0) {
//        	printf("No reply!\n");
		return false;
    	} 
	if (b == SOCKET_ERROR) {
		return false;
	}
	if (FD_ISSET(tcpSocket, &socketRead)) {
		return true;
	}
	return false;
}

bool TCPDataLink::setReuseAddress(bool flag) {
	char optval = (char)flag;
	int result = setsockopt(tcpSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
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




/* Start the Windows sockets
 *	Returns true on success
 */
bool TCPDataLink::startWindowsSockets() {
#ifdef _WIN32
	WSAData socketData;
	int result = WSAStartup(MAKEWORD(2,2), &socketData);
	if (result != NO_ERROR) {
		fprintf(stderr, "Error at WSAStartup() in TCPDataLink\n");
		return false;
	}
#endif
	return true;
}

/* Set up the address structure for the local interface
 * Allowing connections from any IP on he specified port
 */
bool TCPDataLink::setupLocalInterface(int port) {
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	local.sin_port = htons(port);
	return true;
}

/* Set up the address structure for the detination address */
bool TCPDataLink::setupDestinationAddress(const char * address, int port) {
	destination.sin_family = AF_INET;
	destination.sin_addr.s_addr = inet_addr(address);
	destination.sin_port = htons(port);
	return true;
}

/* Create the socket */
bool TCPDataLink::createSocket() {
	tcpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#ifdef _WIN32
	if (tcpSocket == INVALID_SOCKET) {
		fprintf(stderr, "Socket initialisation failed in TCPDataStream. Error %d\n", WSAGetLastError());
		return false;
	}
#elif __linux__
	if (tcpSocket == -1) {
		fprintf(stderr,"Socket initialisation failed in TCPDataStream. Error %d\n", errno);
	}
#endif
	return true;
}

/* Attempt to connect to a server */
bool TCPDataLink::connectAsClient() {
	int result = ::connect(tcpSocket, (sockaddr *)&destination, sizeof(destination));
#ifdef _WIN32
	if (result == SOCKET_ERROR) {
		printf("Unable to connect to TCP server at %s:%d\n", address,port);
		return false;
	}
#elif __linux__
	if (result == -1) {
		printf("Unable to connect to TCP server at %s:%d\n", address,port);
	}
#endif
	return true;
}

/*bool TCPDataLink::createServer() {
	int result = listen(tcpSocket,5);
#ifdef _WIN32
	if (result == SOCKET_ERROR) {
		fprintf(stderr, "Unable to listen on port %d in TCPDataStream. Error %d\n", port, WSAGetLastError());
		return false;
	}
#elif __linux__
	if (result == -1) {
		fprintf(stderr,"Unable to listen on port %d in TCPDataStream. Error %d\n", port, errno);
		return false;
	}
#endif
	return true;
}

bool TCPDataLink::waitForClient() {

}*/


/* Bind the socket to the port */
bool TCPDataLink::bindSocket() {
	int result = bind(tcpSocket, (sockaddr *)&local, sizeof(local));
#ifdef _WIN32
	if (result == SOCKET_ERROR) {
		fprintf(stderr, "Unable to bind to port %d in TCPDataStream. Error %d\n", port, WSAGetLastError());
		return false;
	}
#elif __linux__
	if (result == -1) {
		fprintf(stderr,"Unable to bind to port %d in TCPDataStream. Error %d\n", port, errno);
		return false;
	}
#endif
	return true;
}


/* Receive a packet, assuming data is available (i.e. will block)
 *	Takes an integer representing the maximum number of bytes to read and a pointer
 *	to the char array to return
 *	Returns the actual number of bytes read
 */
int TCPDataLink::receivePacket(int bytes, char * message) {
	sockaddr_in sockDat;
	int addrLength = sizeof(sockDat);
#ifdef _WIN32
	int result = recv(tcpSocket, message, bytes, 0);
	if (result == SOCKET_ERROR) {
		fprintf(stderr, "UDPDataLink failed to receive. Error %d\n", WSAGetLastError());
		return -1;
	}
#elif __linux__
	int result = recv(tcpSocket, message, bytes, 0);
	if (result == -1) {
		fprintf(stderr,"UDPDataLink failed to receive. Error %d\n", errno);
	}
#endif
	return result;
}
