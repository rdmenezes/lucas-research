// DataLinkTestClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



int _tmain(int argc, _TCHAR* argv[])
{

	UDPDataLink *link = new UDPDataLink("131.231.124.183",6432);
	if (!link->connect()) return 0;
	link->setReceiveBuffer(24);
	char msg[128];
	char msg2[128];
	int i = 0;
	while (true) {
		char msg[128] = "hello world";
		int bytes = link->receive(128, msg2);
		Sleep(100);
//		bool v = link->send(msg, 24);
//		printf("%d\n", v);
		
		
		printf("tick %d '%s'\n", i++, msg2);
	}

	return 0;
}

