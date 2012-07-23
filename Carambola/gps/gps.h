#ifndef gps_h
#define gps_h

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <cstring>

#include "SerialDataLink.h"

#define GPS_BAUD 9600
#define GPS_BUFFER_SIZE 1024
//#define INDOOR_DEBUG


enum GPSMessageType {
	GGA, GSA, GSV, RMC, VTG
};

struct GGAData_t {
	float hours;		//UTC
	float minutes;		//UTC
	float seconds;		//UTC
	double latitude;	//decimal degrees
	double longitude;	//decimal degrees
	short fix;		//0 - No fix, 1 - GPS Fix, 2 - Differential GPS Fix
	short satellites;	//number of
	float HDOP;		//Horizontal dilution of precision
	float altitude;		//mamsl
	float geoid;		//Geoidal separtion (m)
	float diff_age;		//Age of differential fix (or null)
};

struct GSAData_t {
	char mode1;		//M - Manual, A - Automatic
	short mode2;		//1 - No fix, 2 - 2D fix, 3 - 3D fix
	short satellite[12];	//Number used per channel
	float PDOP;		//Position dilution of precision
	float HDOP;		//Horizontal dilution of precision
	float VDOP;		//Vertical Diluation of precision
};

//GSV Data post-processed into array of SatelliteData structures
struct SatelliteData_t {
	short id;		//Satellite ID
	short elevation;	//degrees
	short azimuth;		//degrees
	short SNR;		//Signal to noise ratio (dBHz)
};

struct RMCData_t {
	short year;		//UTC
	short month;		//UTC
	short day;		//UTC
	float hours;		//UTC
	float minutes;		//UTC
	float seconds;		//UTC
	char status;		//A - valid, V - invalid
	double latitude;	//decimal degrees
	double longitude;	//decimal degrees
	float groundspeed;	//knots
	float track;		//degrees
	float variation;	//magnetic variation (degrees)
	char mode;		//A - Autonomous, D - Differential, E - Estimated	
};

struct VTGData_t {
	float track;		//degrees true
	float groundspeed;	//knots
	char mode;		//A - Autonomous, D - Differential, E - Estimated
};


class gps : private SerialDataLink {
public:
	gps(const char * port);
	~gps();
	void read();
	short getYear();
	short getDay();
	short getMonth();
	short getHours();
	short getMinutes();
	short getSeconds();
	double getLatitude();
	double getLongitude();

private:
	GPSMessageType getMessageType(const char * message);
	bool processGGA(const char * message);
	bool processGSA(const char * message);
	bool processGSV(const char * message);
	bool processRMC(const char * message);
 	bool processVTG(const char * message);
	bool GGAset;
	bool GSAset;
	bool GSVset;
	bool RMCset;
	bool VTGset;
	GGAData_t GGAData;
	GSAData_t GSAData;
	SatelliteData_t SatelliteData[12];
	RMCData_t RMCData;
	VTGData_t VTGData;

};

#endif
