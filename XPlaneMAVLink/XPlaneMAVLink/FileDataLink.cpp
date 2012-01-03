#include "FileDataLink.h"

/* Constructor for the FileDataLink class, assuming streams already exit */
FileDataLink::FileDataLink(FILE * outputStream, FILE * inputStream) {
	this->outputStream = outputStream;
	this->inputStream = inputStream;
	this->hexIn = false;
	this->hexOut = false;
	outputFile = NULL;
	inputFile = NULL;
}

/* Constructor for the FileDataLink class, assuming class is responsible for the streams */
FileDataLink::FileDataLink(const char * outputFile, const char * inputFile, bool append) {
	this->outputFile = outputFile;
	this->inputFile = inputFile;
	this->append = append;
	this->hexIn = false;
	this->hexOut = false;
}

/* Connect function (terminology inherited from DataLink interface)
 *	Opens the input and output files
 *	Returns true if successful, or if not required (already opened). False on failure
 */
bool FileDataLink::connect() {
	if (outputFile != NULL && inputFile != NULL) {
		return openOutputStream() || openInputStream();
	}
	return true;
}

/* Send function
 *	Outputs specific message up to specified number of bytes
 *	ASCII and Hex (upper case) output supported, lines terminated with \n
 *	Always returns true as there are no meaningful errors worth catching
 */
bool FileDataLink::send(char * message, int bytes) {
	for (int i = 0; i<bytes; i++) {
		if (hexOut) {
			fprintf(outputStream,"%02X ",(unsigned char)message[i]);
		} else {
			fprintf(outputStream,"%c",message[i]);
		}
	}
	fprintf(outputStream, "\n");
	return true;
}
/* Receive function
 *	Takes a maximumg number of bytes to be read and output buffer as arguments
 *	For the special case that the input is being read from stdin a prompt is
 *	printed so the user knows input is expected (and the code hasn't just hung)
 *	Data can be iput as either ASCII of hex (case insensitive)
 *	Returns the actual unmber of caracters read
 */
int FileDataLink::receive(int bytes, char * message) {
	if (inputStream == stdin) {
		printf("(Waiting for input) >>");
	}
	if (hexIn) {
		return decodeHex(message, bytes);
	} else {
		return decodeASCII(message, bytes);
	}
}

/* Disconnect function (terminology from DataLink interface)
 *	Closes the files if we are responsible for them, otherwise does nothing
 *	Returns true if successful (or not required), false on failure
 */ 
bool FileDataLink::disconnect() {
	if (outputFile != NULL && inputFile != NULL) {
		return closeOutputStream() || closeInputStream();
	}
	return true;
}

/* Set Hex format for I/O */
void FileDataLink::setHexOutput(bool flag) {
	hexOut = flag;
}
void FileDataLink::setHexInput(bool flag) {
	hexIn = flag;
}

/* Open output stream function
 *	Opens the file specified for either writing or appending
 *	Returns true if successful, false otherwise
 */
bool FileDataLink::openOutputStream() {
	if (append) {
		outputStream = fopen(outputFile, "a");
	} else {
		outputStream = fopen(outputFile, "w");
	}
	if (outputStream == NULL) {
		fprintf(stderr,"Could not open %s for writing in FileDataLink\n", outputFile);
		return false;
	}
	return true;
}

/* Open input stream function
 *	Opens the file specified for reading
 *	Returns true if successful, false otherwise
 */
bool FileDataLink::openInputStream() {
	inputStream = fopen(inputFile, "r");
	if (inputStream == NULL) {
		fprintf(stderr,"Could not open %s for reading in FileDataLink\n", inputFile);
		return false;
	}
	return true;
}

/* Close functions, return true if successful, false otherwise */
bool FileDataLink::closeOutputStream() {
	int result = fclose(outputStream);
	if (result != 0) {
		fprintf(stderr,"Could not close %s in FileDataLink\n", outputFile);
		return false;
	}
	return true;
}
bool FileDataLink::closeInputStream() {
	int result = fclose(inputStream);
	if (result != 0) {
		fprintf(stderr,"Could not close %s in FileDataLink\n", inputFile);
		return false;
	}
	return true;
}

/* Function to decode Hex input
 *	Takes a pointer to the message output and the maximum number of bytes to read
 *	as parameters.
 *	Returns actual number of characters read.
 */
int FileDataLink::decodeHex(char *message, int bytes) {
	/* Allocate some memory for the hex message
	 * It's 3 times longer than an ASCII message as a char is
	 * 2 Hex values and they are space separated
	 */
	char * tmpMessage = (char *)malloc(bytes*3);
	int length = -1;
	if ((length = readLine((char*)tmpMessage, bytes)) != -1) {
		length++;
		/* Decode each character one at a time */
		for (int i=0; i<length/3; i++) {
			sscanf((char*)tmpMessage+i*3,"%X",(unsigned int*)&message[i]);
		}
		return length/3;
	} else {
		return -1;
	}
}

/* Function to decode ASCII input
 *	Takes pointer to output array and maximum number of bytes to read
 *	Returns actual number of bytes read
 */
int FileDataLink::decodeASCII(char *message, int bytes) {
	return readLine(message, bytes);
}

/* Function to read a line from file
 *	Takes pointer to output array and maximum number of bytes to read
 *	Strips off trailing new line left over by fgets
 *	Returns actual number of bytes read
 */
int FileDataLink::readLine(char *message, int bytes) {
	if (fgets(message,bytes,inputStream) != NULL) {
		int length = strlen(message);
		if (message[length-1] == '\n' || message[length-1] == '\n') {
			message[length-1] = '\0';
		}
		return --length;
	}
	return -1;
}
