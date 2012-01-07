/* MAVLink class to abstract message encoding and decoding
 *	Message encoding and transmission is handled by simple Sender functions
 *
 *	receiveMessage() should be called once per loop (or threaded) to receive the
 *	latest message from the DataLink. This message is then cached locally and
 *	decoded when required. Messages are cached with a time of reception to allow
 *	a timeout condition to be monitor (i.e. was this data received within the last xxx ms)
 */

#ifndef MAVLink_h
#define MAVLink_h

#ifdef _WIN32
	#include <windows.h>
#else
	#include <sys/time.h>
#endif
#include <stdio.h>

#include <map>
#include "mavlink_types.h"
#include "common/common.h"
#include "DataLink.h"

//send/receive buffer size
#define MAVLINK_BUFFER_SIZE 1024

//timeouts
#define MAVLINK_ATTITUDE_TIMEOUT 1000
#define MAVLINK_HEARTBEAT_TIMEOUT 1000
#define MAVLINK_RC_OVERRIDE_TIMEOUT 1000
#define MAVLINK_RAW_GPS_TIMEOUT 1000
#define MAVLINK_VFR_HUD_TIMEOUT 1000
#define MAVLINK_SERVO_TIMEOUT 1000
#define MAVLINK_MODE_TIMEOUT 1000

//Structure for local storage of messages
struct MAVLinkMessage {
	mavlink_message_t msg;
	long timeReceived;
};

class MAVLink {
public:
#ifdef _WIN32
	__declspec( dllexport ) MAVLink(uint8_t mySystemId, uint8_t myComponentId, DataLink *link);
	__declspec( dllexport ) void setTargetComponent(uint8_t targetSystemId, uint8_t targetComponentId);
	__declspec( dllexport ) int receiveMessage();
	
	/* Senders and Getters */
	__declspec( dllexport ) bool sendHeartbeat(uint8_t type, uint8_t autopilotType);
	__declspec( dllexport ) bool sendAttitude(float roll, float pitch, float yaw, float p, float q, float r);
	__declspec( dllexport ) bool getAttitude(float &roll, float &pitch, float &yaw, float &p, float &q, float &r);
	__declspec( dllexport ) bool sendRCOverride(uint16_t c1, uint16_t c2, uint16_t c3, uint16_t c4, uint16_t c5, uint16_t c6, uint16_t c7, uint16_t c8);
	__declspec( dllexport ) bool getRCOverride(uint16_t &c1, uint16_t &c2, uint16_t &c3, uint16_t &c4, uint16_t &c5, uint16_t &c6, uint16_t &c7, uint16_t &c8);
	__declspec( dllexport ) bool sendRawGPS(int fix, float lat, float lng, float alt, float eph, float epv, float v, float crs);
	__declspec( dllexport ) bool getRawGPS(int &fix, float &lat, float &lng, float &alt, float &eph, float &epv, float &v, float &crs);
	__declspec( dllexport ) bool sendVFRHUD(float airspeed, float groundspeed, int16_t heading, uint16_t throttle, float alt, float climb);
	__declspec( dllexport ) bool getVFRHUD(float &airspeed, float &groundspeed, int16_t &heading, uint16_t &throttle, float &alt, float &climb);
	__declspec( dllexport ) bool sendRawServos(uint16_t s1, uint16_t s2, uint16_t s3, uint16_t s4, uint16_t s5, uint16_t s6, uint16_t s7, uint16_t s8);
	__declspec( dllexport ) bool getRawServos(uint16_t &s1, uint16_t &s2, uint16_t &s3, uint16_t &s4, uint16_t &s5, uint16_t &s6, uint16_t &s7, uint16_t &s8);
	__declspec( dllexport ) bool sendScaledServos(int16_t s1, int16_t s2, int16_t s3, int16_t s4, int16_t s5, int16_t s6, int16_t s7, int16_t s8, uint8_t rssi);
	__declspec( dllexport ) bool getScaledServos(int16_t &s1, int16_t &s2, int16_t &s3, int16_t &s4, int16_t &s5, int16_t &s6, int16_t &s7, int16_t &s8, uint8_t &rssi);
	__declspec( dllexport ) bool sendMode(uint32_t mode);
	__declspec( dllexport ) bool getMode(uint32_t &mode);
#else
	MAVLink(uint8_t mySystemId, uint8_t myComponentId, DataLink *link);
	void setTargetComponent(uint8_t targetSystemId, uint8_t targetComponentId);
	int receiveMessage();
	
	/* Senders and Getters */
	bool sendHeartbeat(uint8_t type, uint8_t autopilotType);
	bool sendAttitude(float roll, float pitch, float yaw, float p, float q, float r);
	bool getAttitude(float &roll, float &pitch, float &yaw, float &p, float &q, float &r);
	bool sendRCOverride(uint16_t c1, uint16_t c2, uint16_t c3, uint16_t c4, uint16_t c5, uint16_t c6, uint16_t c7, uint16_t c8);
	bool getRCOverride(uint16_t &c1, uint16_t &c2, uint16_t &c3, uint16_t &c4, uint16_t &c5, uint16_t &c6, uint16_t &c7, uint16_t &c8);
	bool sendRawGPS(int fix, float lat, float lng, float alt, float eph, float epv, float v, float crs);
	bool getRawGPS(int &fix, float &lat, float &lng, float &alt, float &eph, float &epv, float &v, float &crs);
	bool sendVFRHUD(float airspeed, float groundspeed, int16_t heading, uint16_t throttle, float alt, float climb);
	bool getVFRHUD(float &airspeed, float &groundspeed, int16_t &heading, uint16_t &throttle, float &alt, float &climb);
	bool sendRawServos(uint16_t s1, uint16_t s2, uint16_t s3, uint16_t s4, uint16_t s5, uint16_t s6, uint16_t s7, uint16_t s8);
	bool getRawServos(uint16_t &s1, uint16_t &s2, uint16_t &s3, uint16_t &s4, uint16_t &s5, uint16_t &s6, uint16_t &s7, uint16_t &s8);
	bool sendScaledServos(int16_t s1, int16_t s2, int16_t s3, int16_t s4, int16_t s5, int16_t s6, int16_t s7, int16_t s8, uint8_t rssi);
	bool getScaledServos(int16_t &s1, int16_t &s2, int16_t &s3, int16_t &s4, int16_t &s5, int16_t &s6, int16_t &s7, int16_t &s8, uint8_t &rssi);
	bool sendMode(uint32_t mode);
	bool getMode(uint32_t &mode);
#endif
	
private:
	void addMessage();
	bool sendMessage();
	MAVLinkMessage * findMessage(int id);
	long getTime_ms();
	bool checkTimeout(MAVLinkMessage *mm, int timeout);

	DataLink *link;
	uint8_t mySystemId, myComponentId;
	uint8_t targetSystemId, targetComponentId;
	mavlink_message_t msg;
	mavlink_status_t status;
	uint8_t buffer[MAVLINK_BUFFER_SIZE];
#ifdef _WIN32 
	std::map<int, MAVLinkMessage> MessageMap;
#elif __linux__
	std::map<int, MAVLinkMessage> MessageMap;
#else
	MAVLinkMessage MessageMap[255];
#endif
};

#endif
