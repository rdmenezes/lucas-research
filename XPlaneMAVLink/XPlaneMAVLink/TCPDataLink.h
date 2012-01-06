#ifndef TCPDataLink_h
#define TCPDataLink_h


#ifdef _WIN32
	#include <winsock2.h>
	#pragma comment(lib, "Ws2_32.lib")
#endif
#include <stdio.h>
#include "DataLink.h"

class TCPDataLink : public DataLink {
public:
	__declspec( dllexport ) TCPDataLink(const char * address, int port, bool server);
	__declspec( dllexport ) ~TCPDataLink();
	__declspec( dllexport ) bool connect();
	__declspec( dllexport ) bool send(char * message, int bytes);
	__declspec( dllexport ) int receive(int bytes, char * message);
	__declspec( dllexport ) void setReceiveTimeout(int timeout);
	__declspec( dllexport ) bool setReceiveBuffer(int bytes);
	__declspec( dllexport ) bool disconnect();
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
#endif
};

#endif