// TestApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "XBeeAPIDataLink.h"
#include "MAVLink.h"
#include "MAVLinkComponent.h"


int _tmain(int argc, _TCHAR* argv[])
{
	XBeeAPIDataLink *link = new XBeeAPIDataLink("COM6",115200,0x13A200,0x40771103);
	link->connect();
	MAVLink *myMAV = new MAVLink(255,0,link);
	myMAV->setTargetComponent(1,1);


	int counter[256];
	for (int i = 0; i<256; i++) {
		counter[i] = 0;
	}
	char buffer[1024];
	buffer[0] = 0x54;
	buffer[1] = 0x78;
	int i = 1;

//	MAVLinkComponent::loadDatabase();

	MAVLinkComponent *arduwot = new MAVLinkComponent("/aircraft/LU-WOTA/APM");

	printf("%d %d 0x%X 0x%X\n", arduwot->getSystemID(), arduwot->getComponentID(), arduwot->getPhysicalAddressHigh(), arduwot->getPhysicalAddressLow());


/*	myMAV->sendRequestStream(MAV_DATA_STREAM_ALL,0,0);
	myMAV->sendMessages();
	Sleep(100);
	myMAV->sendRequestStream(MAV_DATA_STREAM_EXTRA1,10,1);
	myMAV->sendMessages();*/
	float roll, pitch, yaw, p, q, r;
/*	while (true) {
//		Sleep(10);
		//sprintf(buffer,"%01d\n",i++);
		//printf("%d\n",link->send(buffer,1));
		int i = 0;
		int t = myMAV->receiveMessage();
		if(myMAV->getAttitude(roll, pitch, yaw, p, q, r)) {
			printf("%f\n",yaw);
		}
	}*/
	link->disconnect();

	return 0;
}


