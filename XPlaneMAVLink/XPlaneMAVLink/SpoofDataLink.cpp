#include "SpoofDataLink.h"

SpoofDataLink::SpoofDataLink(const char * input, int iSize, const char * output, int oSize) {
	this->input = input;
	this->output = output;
	this->iSize = iSize;
	this->oSize = oSize;
}
SpoofDataLink::SpoofDataLink(const char * buffer, int size) {
	this->input = buffer;
	this->output = buffer;
	this->iSize = size;
	this->oSize = size;
}

bool SpoofDataLink::connect() {
	return true;
}
bool SpoofDataLink::send(char * message, int bytes) {
	memset((void*)output,'\0', oSize);
	memcpy((void*)output,message,bytes);
	return true;
}
int SpoofDataLink::receive(int bytes, char * message) {
	memcpy(message,(void*)input,bytes);
	memset((void*)input,'\0', iSize);
	return bytes;
}
bool SpoofDataLink::disconnect() {
	return true;
}