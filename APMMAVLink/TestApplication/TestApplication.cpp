// TestApplication.cpp : Defines the entry point for the console application.
//

#include "winsock2.h"
#include "stdafx.h"
#include "XBeeAPIDataLink.h"
#include "SerialDataLink.h"
#include "TCPDataLink.h"
#include "UDPDataLink.h"
#include "MAVLink.h"
#include "MAVLinkComponent.h"


struct CTRL_INPUT {
//serial commands (= Scientific Interface)
short pitch; //Pitch input: -2047..+2047 (0=neutral)
short roll; //Roll input: -2047..+2047 (0=neutral)
short yaw; //(=R/C Stick input) -2047..+2047 (0=neutral)
short thrust; //Collective: 0..4095 = 0..100%
short ctrl;

/*control byte:
bit 0: pitch control enabled
bit 1: roll control enabled
bit 2: yaw control enabled
bit 3: thrust control enabled
These bits can be used to only &
!enable one axis at a time and&
! thus to control the other &
!axes manually. This usually &
!helps a lot to set up and &
!finetune controllers for each&
! axis seperately. */

short chksum;
} myControl;
HANDLE hThreadRead = NULL;
XBeeAPIDataLink *link;
DWORD WINAPI mavThreadRead(LPVOID lpParam);

int _tmain(int argc, _TCHAR* argv[])
{

	SerialDataLink l("COM9",57600);
	l.connect();
//	link = new XBeeAPIDataLink(l,0x13A200,0x407710D9);
//	XBeeAPIDataLink *link2 = new XBeeAPIDataLink(l,0x13A200,0x40771103);
//	DataLink *link = new TCPDataLink("131.231.124.183",5010,false);
	
//	link->connect();
	MAVLink *myMAV = new MAVLink(255,0,&l);
	myMAV->setTargetComponent(2,1);
	//link2->connect();
//	MAVLink *myMAV2 = new MAVLink(255,0,link2);
//	myMAV2->setTargetComponent(1,1);
	int16_t s1,s2,s3,s4,s5,s6,s7,s8;
	uint8_t rssi;

	float roll = 0, pitch = 0, yaw = 0, p = 0, q = 0, r = 0;
	float as,gs,alt,vs;
	uint8_t mode,nav_mode,status;
	uint16_t load,vbat,bat,pack;
	int16_t hdg;
	uint16_t t;
	int32_t lat;
	int32_t lng;
	int32_t alt2;
	int16_t vx,vy,vz;

	myMAV->sendRequestStream(MAV_DATA_STREAM_ALL, 0, 0);
    myMAV->sendMessages();
	Sleep(100);

	myMAV->sendRequestStream(MAV_DATA_STREAM_EXTENDED_STATUS, 3, 1);
    myMAV->sendMessages();
	Sleep(100);
    myMAV->sendRequestStream(MAV_DATA_STREAM_POSITION, 5, 1);
    myMAV->sendMessages();
    Sleep(100);
    myMAV->sendRequestStream(MAV_DATA_STREAM_EXTRA1, 10, 1);
    myMAV->sendMessages();
    Sleep(100);
    myMAV->sendRequestStream(MAV_DATA_STREAM_EXTRA2, 5, 1);
    myMAV->sendMessages();
    Sleep(100);
    myMAV->sendRequestStream(MAV_DATA_STREAM_RAW_SENSORS, 0, 0);
    myMAV->sendMessages();
    Sleep(100);
    myMAV->sendRequestStream(MAV_DATA_STREAM_RC_CHANNELS, 0, 0);        
    myMAV->sendMessages();

/*	myMAV2->sendRequestStream(MAV_DATA_STREAM_ALL, 0, 0);
    myMAV2->sendMessages();
	Sleep(100);
	myMAV2->sendRequestStream(MAV_DATA_STREAM_EXTENDED_STATUS, 3, 1);
    myMAV2->sendMessages();
	Sleep(100);
    myMAV2->sendRequestStream(MAV_DATA_STREAM_POSITION, 5, 1);
    myMAV2->sendMessages();
    Sleep(100);
    myMAV2->sendRequestStream(MAV_DATA_STREAM_EXTRA1, 10, 1);
    myMAV2->sendMessages();
    Sleep(100);
    myMAV2->sendRequestStream(MAV_DATA_STREAM_EXTRA2, 5, 1);
    myMAV2->sendMessages();
    Sleep(100);
    myMAV2->sendRequestStream(MAV_DATA_STREAM_RAW_SENSORS, 0, 0);
    myMAV2->sendMessages();
    Sleep(100);
    myMAV2->sendRequestStream(MAV_DATA_STREAM_RC_CHANNELS, 0, 0);        
    myMAV2->sendMessages();*/


//    if (hThreadRead == NULL) {
//        printf("Creating Thread\n");
 //       hThreadRead = CreateThread( NULL, 0, 
 //           mavThreadRead, NULL, THREAD_TERMINATE, NULL);
 //   }
	Sleep(1000);

	while (true) {
		

		int t = myMAV->receiveMessage();
		if (t<0) {
			printf("%d\n", -t);
		}

//		myMAV2->receiveMessage();

/*		long t2 = myMAV->getVFRHUD(as,gs,hdg,t,alt,vs);

		if (t2 != 0) {
//			printf("2 - VFR %d ", hdg);
		}

		t2 = myMAV->getAttitude(roll, pitch, yaw, p, q, r);
		if (t2 != 0) {
//			printf("2 - Att %f ", roll);
		}

		t2 = myMAV->getGlobalPositionInt(lat, lng, alt2, vx,vy,vz);
		if (t2 != 0) {
//			printf("2 - GPS %d ", lat);
		}

		t2 = myMAV->getSystemStatus(mode,nav_mode,status,load,vbat,bat,pack);
		if (t2 != 0) {
//			printf("2 - status %d\n", vbat);
		}*/
		
/*		long t2 = myMAV2->getVFRHUD(as,gs,hdg,t,alt,vs);

		if (t2 != 0) {
//			printf("1 - VFR %d ", hdg);
		}

		t2 = myMAV2->getAttitude(roll, pitch, yaw, p, q, r);
		if (t2 != 0) {
//			printf("1 - Att %f ", roll);
		}

		t2 = myMAV2->getGlobalPositionInt(lat, lng, alt2, vx,vy,vz);
		if (t2 != 0) {
//			printf("1 - GPS %d ", lat);
		}

		t2 = myMAV2->getSystemStatus(mode,nav_mode,status,load,vbat,bat,pack);
		if (t2 != 0) {
	//		printf("1 - status %d\n", vbat);
		}
//		}*/
	}
	link->disconnect();

	return 0;

  
 /*   SerialDataLink *myLink = new SerialDataLink("COM5", 57600);
    printf("%d\n",myLink->connect());
    
    UDPDataLink *myUDPLink = new UDPDataLink("192.168.23.1", 4321);
    printf("%d\n",myUDPLink->connect());
	myUDPLink->setReceiveBuffer(36);
    MAVLink *myMAVLink = new MAVLink(255,0,myUDPLink);
    myMAVLink->setTargetComponent(30,1);
	float alt;


	while (true) {
		float throttle = (float) 0.0;
		myControl.pitch = 0;   
		myControl.roll = 0;   
		myControl.yaw = 0;   
		myControl.thrust = (short)(4095.0 * throttle);    
		myControl.ctrl = 0x8;
		myControl.chksum = myControl.pitch+ myControl.roll + myControl.yaw + myControl.thrust + myControl.ctrl + 0xAAAA;

		char *ptr = (char*)&myControl;
    
		char buffer[128];
		sprintf(buffer,">*>di");
		myLink->send(buffer, 5);
		Sleep(1);
		myLink->send(ptr, 12);
    
		myMAVLink->receiveMessage();
		float t1,t2,t5;
		int16_t t3;
		uint16_t t4;
		float tmp_alt;
		myMAVLink->getVFRHUD(t1,t2,t3,t4,tmp_alt,t5);
		if (tmp_alt > 0) {
			alt = tmp_alt;
		}
	}
    myLink->disconnect();
    myUDPLink->disconnect();
    myLink = NULL;
    myUDPLink = NULL;
    myMAVLink = NULL;*/



}
