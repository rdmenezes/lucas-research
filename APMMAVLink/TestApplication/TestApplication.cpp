// TestApplication.cpp : Defines the entry point for the console application.
//

#include "winsock2.h"
#include "stdafx.h"
#include "XBeeAPIDataLink.h"
#include "SerialDataLink.h"
#include "TCPDataLink.h"
#include "MAVLink.h"
#include "MAVLinkComponent.h"


int _tmain(int argc, _TCHAR* argv[])
{
//	XBeeAPIDataLink *link = new XBeeAPIDataLink("COM6",115200,0x13A200,0x407710D9);
	DataLink *link = new TCPDataLink("131.231.124.183",5010,false);
	link->connect();
	MAVLink *myMAV = new MAVLink(255,0,link);
	myMAV->setTargetComponent(1,1);
	int16_t s1,s2,s3,s4,s5,s6,s7,s8;
	uint8_t rssi;

	float roll = 0, pitch = 0, yaw = 0, p = 0, q = 0, r = 0;
	float as,gs,alt,vs;
	int16_t hdg;
	uint16_t t;
	while (true) {
		Sleep(2);
		myMAV->receiveMessage();

		long t2 = myMAV->getVFRHUD(as,gs,hdg,t,alt,vs);

		myMAV->sendMessages();
		printf("%d %d\n", t2, hdg);
//		}
	}
	link->disconnect();

	return 0;
}


