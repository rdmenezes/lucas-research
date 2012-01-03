#ifndef DataLink_h
#define DataLink_h

class DataLink {
public:
	virtual bool connect() = 0;
	virtual bool send(char * message, int bytes) = 0;
	virtual int receive(int bytes, char * message) = 0;
	virtual bool disconnect() = 0;
};

#endif