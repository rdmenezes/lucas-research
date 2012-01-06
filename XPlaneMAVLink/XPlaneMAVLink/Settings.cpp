#include "Settings.h"

/* Constructor reads in the settings */
Settings::Settings(const char * filename) {
	this->filename = filename;
	readSettings();
}

/* Destructor saves them */
Settings::~Settings() {
	writeFile();
}

/* Validate the flag parameter */
bool Settings::setFlag(int flag) {
	if (flag < 0 || flag > 2) {
		return false;
	}
	this->flag = flag;
	return true;
}

/* Validate the IP Address 
 *	Only supports IPv4 of the format
 *	{0-255}.{0-255}.{0-255}.{0-255}
 *	Note that 0.0.0.0 is also invalid
 */
bool Settings::setIP(char * ip) {
	int a,b,c,d;
	int v = sscanf(ip,"%d.%d.%d.%d",&a,&b,&c,&d);
	if (v != 4) {
		return false;
	}
	if ((a == 0) && (b == 0) && (c == 0) && (d == 0)) {
		return false;
	}
	if ((a/256>=1) || (b/256>=1) || (c/256>=1) || (d/256>=1)) {
		return false;
	}
	if ((a<0) || (b<0) || (c<0) || (d<0)) {
		return false;
	}
	sprintf(this->ip,"%s",ip);
	return true;
}

/* Validate the port number */
bool Settings::setPort(int port) {
	if (port < 0 || port > 65536) {
		return false;
	}
	this->port = port;
	return true;
}

/* NO VALIDATION FOR COMPORT AS NOT CURRENTLY SUPPORTED! */
bool Settings::setComPort(char * com) {
	sprintf(this->com,"%s",com);
	return true;
}
/* NO VALIDATION FOR BAUD RATE AS NOT CURRENTLY SUPPORTED! */
bool Settings::setBaudRate(int baud) {
	this->baud = baud;
	return true;
}

/* Some getters */
int Settings::getFlag() {
	return flag;
}
char * Settings::getIP() {
	return ip;
}
int Settings::getPort() {
	return port;
}
char * Settings::getComPort() {
	return com;
}
int Settings::getBaudRate() {
	return baud;
}

/* Load from file */
bool Settings::load() {
	return readSettings();
}

/* Save to file */
bool Settings::save() {
	return writeFile();
}

/* Read in settings, or default them if file doesn't exist */
//	TODO: Defaults should go somewhere else?
bool Settings::readSettings() {
	if (!readFile()) {
		flag = 0;
		sprintf(ip,"0.0.0.0");
		port = 5760;
		sprintf(com,"COM0");
		baud = 115200;
		return false;
	}
	return true;
}

/* Read from a file */
bool Settings::readFile() {
	char line[128];
	char param[128];
	int paramCount = 0;

	FILE * file = fopen(filename,"r");
	if (file == NULL) {
		return false;
	}
	printf("File opened...\n");
	while (fscanf(file,"%s",param) != EOF) {
		if (strcmp(param,"flag") == 0) {
			fscanf(file, "%d",&flag);
			paramCount++;
			continue;
		}
		if (strcmp(param,"ip") == 0) {
			fscanf(file, "%s",ip);
			paramCount++;
			continue;
		}
		if (strcmp(param,"port") == 0) {
			fscanf(file, "%d",&port);
			paramCount++;
			continue;
		}
		if (strcmp(param,"com") == 0) {
			fscanf(file, "%s",com);
			paramCount++;
			continue;
		}
		if (strcmp(param,"baud") == 0) {
			fscanf(file, "%d",&baud);
			paramCount++;
			continue;
		}
	}
	fclose(file);
	if (paramCount == 5) {
		return true;
	}
	return false;
}

/* Write to file*/
bool Settings::writeFile() {
	FILE * file = fopen(filename,"w");
	if (file == NULL) {
		return false;
	}
	fprintf(file, "flag %d\n",flag);
	fprintf(file, "ip %s\n",ip);
	fprintf(file, "port %d\n",port);
	fprintf(file, "com %s\n",com);
	fprintf(file, "baud %d\n",baud);
	fclose(file);
	return true;
}