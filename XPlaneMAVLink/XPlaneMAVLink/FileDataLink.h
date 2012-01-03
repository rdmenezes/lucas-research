/* Specialisation of the DataLink interface for the file writing
 *	Allows both writing to and reading from a file in either ASCII or Hex
 *		ASCII I/O is default but not recommended in binary streams
 *		Hex I/O is useful for debugging or logging of binary streams
 */

#ifndef FileDataLink_h
#define FileDataLink_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataLink.h"

class FileDataLink : public DataLink {
public:
	__declspec( dllexport ) FileDataLink(FILE * outputStream, FILE * inputStream);
	__declspec( dllexport ) FileDataLink(const char * outputFile, const char * inputFile, bool append);
	__declspec( dllexport ) bool connect();
	__declspec( dllexport ) bool send(char * message, int bytes);
	__declspec( dllexport ) int receive(int bytes, char * message);
	__declspec( dllexport ) bool disconnect();
	__declspec( dllexport ) void setHexOutput(bool flag);
	__declspec( dllexport ) void setHexInput(bool flag);

private:
	bool openOutputStream();
	bool openInputStream();
	bool closeOutputStream();
	bool closeInputStream();
	int decodeASCII(char *message, int bytes);
	int decodeHex(char *message, int bytes);
	int readLine(char *message, int bytes);

	FILE * outputStream;
	FILE * inputStream;
	const char * outputFile;
	const char * inputFile;
	bool append;
	bool hexOut;
	bool hexIn;
};

#endif