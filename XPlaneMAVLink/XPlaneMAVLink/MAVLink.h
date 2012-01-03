#ifndef MAVLink_h
#define MAVLink_h

#define MAVLINK_BUFFER_SIZE 1024
#define MAVLINK_ATTITUDE_TIMEOUT 1000
#define MAVLINK_HEARTBEAT_TIMEOUT 1000
#define MAVLINK_RC_OVERRIDE_TIMEOUT 1000


#include <stdio.h>
#include <windows.h>
#include <map>
#include "mavlink_types.h"//"mavlink_types.h"
#include "common\common.h"
#include "DataLink.h"

struct MAVLinkMessage {
	mavlink_message_t msg;
	int timeReceived;
};

class MAVLink {
public:
	__declspec( dllexport ) MAVLink(uint8_t mySystemId, uint8_t myComponentId, DataLink *link);
	__declspec( dllexport ) void setTargetComponent(uint8_t targetSystemId, uint8_t targetComponentId);
	__declspec( dllexport ) bool sendHeartbeat(uint8_t type, uint8_t autopilotType);
	__declspec( dllexport ) bool sendAttitude(float roll, float pitch, float yaw, float p, float q, float r);
	__declspec( dllexport ) bool getAttitude(float &roll, float &pitch, float &yaw, float &p, float &q, float &r);
	__declspec( dllexport ) bool sendRCOverride(uint16_t c1, uint16_t c2, uint16_t c3, uint16_t c4, uint16_t c5, uint16_t c6, uint16_t c7, uint16_t c8);
	__declspec( dllexport ) bool getRCOverride(uint16_t &c1, uint16_t &c2, uint16_t &c3, uint16_t &c4, uint16_t &c5, uint16_t &c6, uint16_t &c7, uint16_t &c8);
	__declspec( dllexport ) bool receiveMessage();
private:
	bool sendMessage();
	MAVLinkMessage * findMessage(int id);
	int getTime_ms();
	bool checkTimeout(MAVLinkMessage *mm, int timeout);
	DataLink *link;
	uint8_t mySystemId, myComponentId;
	uint8_t targetSystemId, targetComponentId;

	mavlink_message_t msg;
	mavlink_status_t status;
	uint8_t buffer[MAVLINK_BUFFER_SIZE];

//	std::map<int, MAVLinkMessage> MessageMap;
	MAVLinkMessage MessageMap[255];
};

#endif