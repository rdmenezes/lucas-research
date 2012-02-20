/* This class contains all the details of the available MAVLink Components
 *	A database file is used to keep track of the data, this file is read
 *	once and the data cached. New instances of this class pass a unique
 *	identifier and receive that particular components information.
 *
 *	Information handled is the system and component ID and a physical
 *	address corresponding to the XBee modules 64-bit address
 */


#ifndef MAVLinkComponet_h
#define MAVLinkComponet_h

#include <iostream>
#include <fstream>
#include <string>

#define MAXIMUM_COMPONENTS 1024

using namespace std;
#ifdef _WIN32
	class __declspec( dllexport ) MAVLinkComponent {
#else
	class MAVLinkComponent {
#endif
public:
	MAVLinkComponent(const char * identifier);
	
	int getSystemID();
	int getComponentID();
	long getPhysicalAddressHigh();
	long getPhysicalAddressLow();
	bool isValidComponent();
private:
	
	static bool loadDatabase(const char * filename = "components.txt");
	static bool isComment(string line);
	
	
	static char identifiers[MAXIMUM_COMPONENTS][256];
	static int systemIDs[MAXIMUM_COMPONENTS];
	static int componentIDs[MAXIMUM_COMPONENTS];
	static long physicalAddress[MAXIMUM_COMPONENTS][2];
	static int numberOfComponents;

	

	int myComponentNumber;
};

#endif