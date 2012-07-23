#include "gps.h"


gps::gps(const char * port) : SerialDataLink(port, GPS_BAUD) {
	connect();
	GGAset = false;
	GSAset = false;
	GSVset = false;
	RMCset = false;
	VTGset = false;
}
gps::~gps() {
	disconnect();
}

void gps::read() {
	char data[GPS_BUFFER_SIZE];

//	int n = receive(GPS_BUFFER_SIZE, data);
	
//	printf("-----\n");

	for (int i = 0; i<GPS_BUFFER_SIZE; i++) {
		receive(1,data+i);
//		printf("%c", data[i]);
		if (data[i] == '\n') {
			break;
		}
	}
//	return;
	switch (getMessageType(data)) {
	case GGA:
#ifdef INDOOR_DEBUG
		GGAset = processGGA("$GPGGA,064951.123,2307.1256,N,12016.4438,W,1,8,0.95,39.9,M,17.8,M,,*65");
#else
		GGAset = processGGA(data);
#endif
		break;
	case GSA:
#ifdef INDOOR_DEBUG
		GSAset = processGSA("$GPGSA,A,3,29,21,26,15,18,09,06,10,,,,,2.32,0.95,2.11*00");
#else
		GSAset = processGSA(data);
#endif
		break;
	case GSV:
#ifdef INDOOR_DEBUG
		GSVset = processGSV("$GPGSV,3,1,09,29,36,029,42,21,46,314,43,26,44,020,43,15,21,321,39*7D");
		GSVset = processGSV("$GPGSV,3,2,09,18,26,314,40,09,57,170,44,06,20,229,37,10,26,084,37*77");
		GSVset = processGSV("$GPGSV,3,3,09,07,,,26*73");
#else
		GSVset = processGSV(data);
#endif
		break;
	case RMC:
#ifdef INDOOR_DEBUG
		RMCset = processRMC("$GPRMC,064951.000,A,2307.1256,N,12016.4438,E,0.03,165.48,260406,3.05,W,A*2C");
#else
		RMCset =processRMC(data);
#endif
		break;
	case VTG:
#ifdef INDOOR_DEBUG
		VTGset = processVTG("$GPVTG,165.48,T,,M,0.03,N,0.06,K,A*37");
#else
		VTGset = processVTG(data);
#endif
		break;
	}
}

// GGA, GSA, GSV, RMC, VTG
GPSMessageType gps::getMessageType(const char * message) {
	if (strstr(message, "$GPGGA") == message || strstr(message, "GPGGA") == message) {
//		printf("GGA\n");
		return GGA;
	}
	if (strstr(message, "$GPGSA") == message || strstr(message, "GPGSA") == message) {
//		printf("GSA\n");
		return GSA;
	}
	if (strstr(message, "$GPGSV") == message || strstr(message, "GPGSV") == message) {
//		printf("GSV\n");
		return GSV;
	}
	if (strstr(message, "$GPRMC") == message || strstr(message, "GPRMC") == message) {
//		printf("RMC\n");
		return RMC;
	}
	if (strstr(message, "$GPVTG") == message || strstr(message, "GPVTG") == message) {
//		printf("VTG\n");
		return VTG;
	}

}

bool gps::processGGA(const char * message) {
	char * str;
	char * mes = strdupa(message+7);
	float latDegs, latMins, longDegs, longMins;
	char latFlag, longFlag, altUnits, geoidUnits, latSign = 0, longSign = 0;

	str = strsep(&mes, ",*");
	sscanf(str,"%2f%2f%6f", &(GGAData.hours), &(GGAData.minutes), &(GGAData.seconds));
	str = strsep(&mes, ",*");
	sscanf(str,"%2f%7f", &latDegs, &latMins);
	str = strsep(&mes, ",*");
	sscanf(str,"%c", &latFlag);
	str = strsep(&mes, ",*");
	sscanf(str,"%2f%7f", &longDegs, &longMins);
	str = strsep(&mes, ",*");
	sscanf(str,"%c", &longFlag);
	str = strsep(&mes, ",*");
	sscanf(str,"%d", &(GGAData.fix));
	str = strsep(&mes, ",*");
	sscanf(str,"%d", &(GGAData.satellites));
	str = strsep(&mes, ",*");
	sscanf(str,"%f", &(GGAData.HDOP));
	str = strsep(&mes, ",*");
	sscanf(str,"%f", &(GGAData.altitude));
	str = strsep(&mes, ",*");
	sscanf(str,"%c", &altUnits);
	str = strsep(&mes, ",*");
	sscanf(str,"%f", &(GGAData.geoid));
	str = strsep(&mes, ",*");
	sscanf(str,"%c", &geoidUnits);
	str = strsep(&mes, ",*");
	sscanf(str,"%f", &(GGAData.diff_age));

	if (latFlag == 'N') {
		latSign = 1;
	} else if (latFlag == 'S') {
		latSign = -1;
	}
	if (longFlag == 'E') {
		longSign = 1;
	} else if (longFlag == 'W') {
		longSign = -1;
	}

	GGAData.latitude = (double)(latSign)*((double)(latDegs) + (double)(latMins) / 60.0);
	GGAData.longitude = (double)(longSign)*((double)(longDegs) + (double)(longMins) / 60.0);

/*	printf("GGA Data:\n");
	printf("        Time: %2.0f:%2.0f:%5f\n", GGAData.hours, GGAData.minutes, GGAData.seconds);
	printf("    Position: %f, %f\n", GGAData.latitude, GGAData.longitude);
	printf("         Fix: %d\n", GGAData.fix);
	printf("  Satellites: %d\n", GGAData.satellites);
	printf("        HDOP: %f\n", GGAData.HDOP);
	printf("    Altitude: %f\n", GGAData.altitude);
	printf("       Geoid: %f\n", GGAData.geoid);
	printf("   Diff. Age: %f\n", GGAData.diff_age);
*/
	return true;
}
bool gps::processGSA(const char * message) {
	char * str;
	char * mes = strdupa(message+7);

	str = strsep(&mes, ",*");
	sscanf(str, "%c", &(GSAData.mode1));
	str = strsep(&mes, ",*");
	sscanf(str, "%d", &(GSAData.mode2));
	str = strsep(&mes, ",*");
	sscanf(str, "%d", &(GSAData.satellite[0]));
	str = strsep(&mes, ",*");
	sscanf(str, "%d", &(GSAData.satellite[1]));
	str = strsep(&mes, ",*");
	sscanf(str, "%d", &(GSAData.satellite[2]));
	str = strsep(&mes, ",*");
	sscanf(str, "%d", &(GSAData.satellite[3]));
	str = strsep(&mes, ",*");
	sscanf(str, "%d", &(GSAData.satellite[4]));
	str = strsep(&mes, ",*");
	sscanf(str, "%d", &(GSAData.satellite[5]));
	str = strsep(&mes, ",*");
	sscanf(str, "%d", &(GSAData.satellite[6]));
	str = strsep(&mes, ",*");
	sscanf(str, "%d", &(GSAData.satellite[7]));
	str = strsep(&mes, ",*");
	sscanf(str, "%d", &(GSAData.satellite[8]));
	str = strsep(&mes, ",*");
	sscanf(str, "%d", &(GSAData.satellite[9]));
	str = strsep(&mes, ",*");
	sscanf(str, "%d", &(GSAData.satellite[10]));
	str = strsep(&mes, ",*");
	sscanf(str, "%d", &(GSAData.satellite[11]));
	str = strsep(&mes, ",*");
	sscanf(str, "%f", &(GSAData.PDOP));
	str = strsep(&mes, ",*");
	sscanf(str, "%f", &(GSAData.HDOP));
	str = strsep(&mes, ",*");
	sscanf(str, "%f", &(GSAData.VDOP));

/*	printf("GSA Data:\n");
	printf("  Mode 1: %c\n",GSAData.mode1);
	printf("  Mode 2: %d\n",GSAData.mode2);
	printf("   Sat 1: %d\n", GSAData.satellite[0]);
	printf("   Sat 2: %d\n", GSAData.satellite[1]);
	printf("   Sat 3: %d\n", GSAData.satellite[2]);
	printf("   Sat 4: %d\n", GSAData.satellite[3]);
	printf("   Sat 5: %d\n", GSAData.satellite[4]);
	printf("   Sat 6: %d\n", GSAData.satellite[5]);
	printf("   Sat 7: %d\n", GSAData.satellite[6]);
	printf("   Sat 8: %d\n", GSAData.satellite[7]);
	printf("   Sat 9: %d\n", GSAData.satellite[8]);
	printf("  Sat 10: %d\n", GSAData.satellite[9]);
	printf("  Sat 11: %d\n", GSAData.satellite[10]);
	printf("  Sat 12: %d\n", GSAData.satellite[11]);
	printf("    PDOP: %f\n", GSAData.PDOP);
	printf("    HDOP: %f\n", GSAData.HDOP);
	printf("    VDOP: %f\n", GSAData.VDOP);
*/
	return true;
}

bool gps::processGSV(const char * message) {
	char * str;
	char * mes = strdupa(message+7);

	short numberOfMsgs, msgNumber, numberOfSats;

	str = strsep(&mes, ",*");
	sscanf(str, "%d", &numberOfMsgs);
	str = strsep(&mes, ",*");
	sscanf(str, "%d", &msgNumber);
	str = strsep(&mes, ",*");
	sscanf(str, "%d", &numberOfSats);

/*	printf("Satellite Data:\n");
	printf("  Number of Messages: %d\n",numberOfMsgs);
	printf("      Message Number: %d\n",msgNumber);
	printf("      Number of Sats: %d\n",numberOfSats);
*/
	int satCount = numberOfSats - (msgNumber-1)*4;

	if (satCount > 4) {
		satCount = 4;
	}

	for (int i = 0; i<satCount; i++) {
		str = strsep(&mes, ",*");
		sscanf(str, "%d", &(SatelliteData[(msgNumber-1)*4 + i].id));
		str = strsep(&mes, ",*");
		sscanf(str, "%d", &(SatelliteData[(msgNumber-1)*4 + i].elevation));
		str = strsep(&mes, ",*");
		sscanf(str, "%d", &(SatelliteData[(msgNumber-1)*4 + i].azimuth));
		str = strsep(&mes, ",*");
		sscanf(str, "%d", &(SatelliteData[(msgNumber-1)*4 + i].SNR));
/*		printf("        Satellite ID: %d\n",(SatelliteData[(msgNumber-1)*4 + i].id));
		printf("      Satellite Elev: %d\n",(SatelliteData[(msgNumber-1)*4 + i].elevation));
		printf("     Satellite Azmth: %d\n",(SatelliteData[(msgNumber-1)*4 + i].azimuth));
		printf("       Satellite SNR: %d\n",(SatelliteData[(msgNumber-1)*4 + i].SNR));
*/	}
	
	return true;
}
bool gps::processRMC(const char * message) {
	char * str;
	char * mes = strdupa(message+7);
	float latDegs, latMins, longDegs, longMins, var;
	char latFlag, longFlag, varFlag, altUnits, geoidUnits, latSign = 0, longSign = 0, varSign = 0;

	str = strsep(&mes, ",*");
	sscanf(str,"%2f%2f%6f", &(RMCData.hours), &(RMCData.minutes), &(RMCData.seconds));
	str = strsep(&mes, ",*");
	sscanf(str,"%c", &(RMCData.status));
	str = strsep(&mes, ",*");
	sscanf(str,"%2f%7f", &latDegs, &latMins);
	str = strsep(&mes, ",*");
	sscanf(str,"%c", &latFlag);
	str = strsep(&mes, ",*");
	sscanf(str,"%2f%7f", &longDegs, &longMins);
	str = strsep(&mes, ",*");
	sscanf(str,"%c", &longFlag);
	str = strsep(&mes, ",*");
	sscanf(str,"%f", &(RMCData.groundspeed));
	str = strsep(&mes, ",*");
	sscanf(str,"%f", &(RMCData.track));
	str = strsep(&mes, ",*");
	sscanf(str,"%2hd%2hd%2hd", &(RMCData.day), &(RMCData.month), &(RMCData.year));
	str = strsep(&mes, ",*");
	sscanf(str,"%f", &var);
	str = strsep(&mes, ",*");
	sscanf(str,"%c", &varFlag);
	str = strsep(&mes, ",*");
	sscanf(str,"%c", &(RMCData.mode));

	if (latFlag == 'N') {
		latSign = 1;
	} else if (latFlag == 'S') {
		latSign = -1;
	}
	if (longFlag == 'E') {
		longSign = 1;
	} else if (longFlag == 'W') {
		longSign = -1;
	}
	if (varFlag == 'E') {
		varSign = 1;
	} else if (longFlag == 'W') {
		varSign = -1;
	}

	RMCData.latitude = (double)(latSign)*((double)(latDegs) + (double)(latMins) / 60.0);
	RMCData.longitude = (double)(longSign)*((double)(longDegs) + (double)(longMins) / 60.0);
	RMCData.variation = ((float)varSign)*var;


/*	printf("RMC Data:\n");
	printf("        Date: %d/%d/%d\n", RMCData.day, RMCData.month, RMCData.year);	
	printf("        Time: %2.0f:%2.0f:%5f\n", RMCData.hours, RMCData.minutes, RMCData.seconds);
	printf("    Position: %f, %f\n", RMCData.latitude, RMCData.longitude);
	printf(" Groundspeed: %f\n", RMCData.groundspeed);
	printf("       Track: %f\n", RMCData.track);
	printf("   Variation: %f\n", RMCData.variation);
	printf("        Mode: %c\n", RMCData.mode);
*/
	return true;
}
bool gps::processVTG(const char * message) {
	char * str;
	char * mes = strdupa(message+7);
	str = strsep(&mes, ",*");
	sscanf(str,"%f", &(VTGData.track));
	str = strsep(&mes, ",*");
	//ignore reference
	str = strsep(&mes, ",*");
	//ignore 2nd course
	str = strsep(&mes, ",*");
	//ignore 2nd course reference
	str = strsep(&mes, ",*");
	sscanf(str,"%f", &(VTGData.groundspeed));
	str = strsep(&mes, ",*");
	//ignore reference
	str = strsep(&mes, ",*");
	//ignore 2nd speed
	str = strsep(&mes, ",*");
	//ignore 2nd speed reference
	str = strsep(&mes, ",*");
	sscanf(str,"%c", &(VTGData.mode));

/*	printf("VTG Data:\n");
	printf(" Groundspeed: %f\n", VTGData.groundspeed);
	printf("       Track: %f\n", VTGData.track);
	printf("        Mode: %c\n", VTGData.mode);
*/
	return true;
}

short gps::getYear() {
	while (!RMCset) {
		read();
	}
	return RMCData.year;
}
short gps::getDay() {
	while (!RMCset) {
		read();
	}
	return RMCData.day;
}
short gps::getMonth() {
	while (!RMCset) {
		read();
	}
	return RMCData.month;
}
short gps::getHours() {
	while (!RMCset) {
		read();
	}
	return (short)RMCData.hours;
}
short gps::getMinutes() {
	while (!RMCset) {
		read();
	}
	return (short)RMCData.minutes;
}
short gps::getSeconds() {
	while (!RMCset) {
		read();
	}
	return (short)RMCData.seconds;
}
double gps::getLatitude() {
	while (!RMCset) {
		read();
	}
	return RMCData.latitude;
}
double gps::getLongitude() {
	while (!RMCset) {
		read();
	}
	return RMCData.longitude;
}


int main(int argc, char *argv[]) {
	gps * myGPS = new gps("/dev/ttyS0");

	if (argc == 1 || strcmp(argv[1], "position") == 0){
		printf("%f, %f\n", myGPS->getLatitude(), myGPS->getLongitude());
	} else {
		if (strcmp(argv[1], "time") == 0) {
			printf("%02d:%02d:%02d\n",
				myGPS->getHours(), myGPS->getMinutes(), myGPS->getSeconds());
		}
		if (strcmp(argv[1], "date") == 0) {
			printf("20%02d-%02d-%02d\n",
				myGPS->getYear(), myGPS->getMonth(), myGPS->getDay());
		}
		if (strcmp(argv[1], "datetime") == 0) {
			printf("20%02d-%02d-%02d %02d:%02d:%02d\n",
				myGPS->getYear(), myGPS->getMonth(), myGPS->getDay(),
				myGPS->getHours(), myGPS->getMinutes(), myGPS->getSeconds());
		}
	}
	delete myGPS;

}
