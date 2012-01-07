#ifndef TCPDataLink_h
#define TCPDataLink_h


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

class TCPDataLink : public DataLink {
public:
#ifdef _WIN32
	__declspec( dllexport ) TCPDataLink(const char * address, int port, bool server);
	__declspec( dllexport ) ~TCPDataLink();
	__declspec( dllexport ) bool connect();
	__declspec( dllexport ) bool send(char * message, int bytes);
	__declspec( dllexport ) int receive(int bytes, char * message);
	__declspec( dllexport ) void setReceiveTimeout(int timeout);
	__declspec( dllexport ) bool setReceiveBuffer(int bytes);
	__declspec( dllexport ) bool disconnect();
#else
	TCPDataLink(const char * address, int port, bool server);
	~TCPDataLink();
	bool connect();
	bool send(char * message, int bytes);
	int receive(int bytes, char * message);
	void setReceiveTimeout(int timeout);
	bool setReceiveBuffer(int bytes);
	bool disconnect();
#endif
private:
	bool startWindowsSockets();
	bool setupLocalInterface(int port);
	bool setupDestinationAddress(const char * address, int port);
	bool createSocket();
	bool connectAsClient();
	bool createServer();
	bool waitForClient();
	bool bindSocket();
	bool setReuseAddress(bool flag);
	
	bool socketDataAvailable();
	int receivePacket(int bytes, char * message);
	const char * address;
	int port;
	int timeout;
	struct sockaddr_in local, destination;
#ifdef _WIN32
	SOCKET tcpSocket;
	SOCKET serverSocket;
#elif __linux__
	int tcpSocket;
	int serverSocket;
#endif
};

#endif
