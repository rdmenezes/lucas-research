// TestApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	SerialDataLink *link = new SerialDataLink("COM4",57600);
//	DataLink *link = new TCPDataLink("131.231.124.183",5010,false);
	link->connect();
	MAVLink *myMAV = new MAVLink(1,1,link);
	myMAV->setTargetComponent(255,0);
	int16_t s1,s2,s3,s4,s5,s6,s7,s8;
	uint8_t rssi;

	float roll = 0, pitch = 0, yaw = 0, p = 0, q = 0, r = 0;
	float as = 1.0,gs = 1.0,alt = 1.0,vs = 1.0;
	int16_t hdg = 1;
	uint16_t t = 1;
	int32_t lat = 6;
	while (true) {
		Sleep(20);
		long t2 = myMAV->sendVFRHUD(as,gs,hdg++,t,alt,vs);
		Sleep(20);
		t2 = myMAV->sendAttitude(roll, pitch, yaw, p, q, r);
		Sleep(20);
		t2 = myMAV->sendGlobalPositionInt(lat++,10,10,10,10,10);
		Sleep(20);
		myMAV->sendMessages();
		roll = roll + 0.1;

		printf("%d %d\n", t2, hdg);
//		}
	}
	link->disconnect();

	return 0;
}
