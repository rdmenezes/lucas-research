// DataLinkTestClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DebugDataLink.h"
#include "SpoofDataLink.h"
#include "MAVLink.h"


int _tmain(int argc, _TCHAR* argv[])
{
//	UDPDataLink *link = new UDPDataLink("131.231.124.183",6432);

	char buffer[1024];
	float roll, pitch, yaw, p, q, r;
	uint16_t c1, c2, c3, c4, c5, c6, c7, c8;

	SpoofDataLink * link = new SpoofDataLink(buffer, 1024);
	MAVLink * myMAV = new MAVLink(10,0,link);

	myMAV->setTargetComponent(10,1);

	if (!link->connect()) return 0;
	
	int c = 0;

	while (true) {
		if ((c++)%2==0) {
			myMAV->sendAttitude(1,2,3,4,5,6);
		} else {
			myMAV->sendRCOverride(1500,1500,1500,1500,1500,1500,1550,1550);
		}
		myMAV->receiveMessage();

		Sleep(400);
		
		bool n = myMAV->getAttitude(roll, pitch, yaw, p, q, r);
		printf("%d - %f %f %f %f %f %f\n", n, roll, pitch, yaw, p, q, r);
		
		n = myMAV->getRCOverride(c1, c2, c3, c4, c5, c6, c7, c8);
		printf("%d - %d %d %d %d %d %d %d %d\n", n, c1, c2, c3, c4, c5, c6, c7, c8);
		
	}

	return 0;
}

