/* Convenient little class to store our parameters to a file
 *	Only stores TCP and Serial parameters
 *	TODO: Make this a bit more generic
 */

#ifndef Settings_h
#define Settings_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Settings {
public:
	Settings(const char * filename);
	~Settings();
	bool setFlag(int flag);
	bool setIP(char * ip);
	bool setPort(int port);
	bool setComPort(char * com);
	bool setBaudRate(int baud);
	int getFlag();
	char * getIP();
	int getPort();
	char * getComPort();
	int getBaudRate();
	bool load();
	bool save();
private:
	bool readSettings();
	bool readFile();
	bool writeFile();
	const char * filename;
	int flag;
	char ip[128];
	int port;
	char com[16];
	int baud;
};

#endif