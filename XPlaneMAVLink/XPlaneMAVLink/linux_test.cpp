// DataLinkTestClient.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <unistd.h>
#include "TCPDataLink.h"
#include "MAVLink.h"


int main()
{
//	UDPDataLink *link = new UDPDataLink("131.231.124.183",6432);

	char buffer[1024];
	float roll, pitch, yaw, p, q, r;
	uint16_t c1, c2, c3, c4, c5, c6, c7, c8;

	TCPDataLink * link = new TCPDataLink("131.231.124.198", 6432, false);
	MAVLink * myMAV = new MAVLink(10,0,link);

	myMAV->setTargetComponent(10,1);

	if (!link->connect()) return 0;
	
	int c = 0;

	while (true) {
		myMAV->receiveMessage();

		usleep(400000);
		
		bool n = myMAV->getAttitude(roll, pitch, yaw, p, q, r);
		printf("%d - %f %f %f %f %f %f\n", n, roll, pitch, yaw, p, q, r);
		
		n = myMAV->getRCOverride(c1, c2, c3, c4, c5, c6, c7, c8);
		printf("%d - %d %d %d %d %d %d %d %d\n", n, c1, c2, c3, c4, c5, c6, c7, c8);
		
	}

	return 0;
}

