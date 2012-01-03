#include "MAVLink.h"

/* Constructor for the MAVLink class
 *	Takes the id's of this system and component and a pointer to the datalink to be used
 */
MAVLink::MAVLink(uint8_t mySystemId, uint8_t myComponentId, DataLink *link) {
	this->mySystemId = mySystemId;
	this->myComponentId = myComponentId;
	this->link = link;
}

/* Set the id of the component to which messages should be sent
 *	Note this is not implemented on a lot of messages, see the MAVLink documentation
 *	to figure out which ones
 */
void MAVLink::setTargetComponent(uint8_t targetSystemId, uint8_t targetComponentId) {
	this->targetSystemId = targetSystemId;
	this->targetComponentId = targetComponentId;
}

/* Receive a message from the DataLink
 *	This stores the latest message received for use by the getters
 *	This function should be called at least once per loop to ensure all packets
 *	get captured. If running on a PC you should consider threading a call to this
 *	function so it is called regularly in the background
 */
bool MAVLink::receiveMessage() {
	int msg_len = link->receive(MAVLINK_BUFFER_SIZE,(char*)buffer);
	for (int i=0; i<msg_len; i++) {
		if (mavlink_parse_char(0,buffer[i],&msg,&status)) {
			addMessage();
			return true;
		}
	}
	return false;
}

/* Add the latest packet to local storage, overriding previous examples
 *	Time of receipt is captured to allow the timeout conditions to be
 *	evaluated by the getters
 */
void MAVLink::addMessage() {
	MAVLinkMessage mm;
	mm.msg = msg;
	mm.timeReceived = getTime_ms();
	MessageMap[msg.msgid] = mm;
}

/* Send a message
 *	Once the buffer has been filled by a sender this function is called
 *	to send it to the DataLink.
 *	Returns true if successful, false otherwise
 */
bool MAVLink::sendMessage() {
	int msg_len = mavlink_msg_to_send_buffer(buffer, &msg);
	return link->send((char *)buffer, msg_len);
}

/* Get the time (Milliseconds since midnight)
 *	TODO: update this to the UNIX epoch
 */
int MAVLink::getTime_ms() {
	SYSTEMTIME st;
	GetSystemTime(&st);
    return st.wMilliseconds
		+ st.wSecond*1000
		+ st.wMinute*1000*60
		+ st.wHour*1000*60*60;
}

/* Check the for the timeout condition for a specific message
 *	If a packet was received greater than 'timeout' milliseconds ago
 *	this function returns false
 */
bool MAVLink::checkTimeout(MAVLinkMessage *mm, int timeout) {
	if ((getTime_ms()-mm->timeReceived)<timeout) {
		return true;
	}
	return false;
}

/*************************** Senders and Getters ***************************/
/* All Getters are passed parameters by reference and return true is the timeout
 * condition has not been encoutned (false if timed out)
 */

/* Heatbeat */
bool MAVLink::sendHeartbeat(uint8_t type, uint8_t autopilotType) {
	mavlink_msg_heartbeat_pack(mySystemId,myComponentId,&msg,type,autopilotType);
	return sendMessage();
}

/* Attitude Sender */
bool MAVLink::sendAttitude(float roll, float pitch, float yaw, float p, float q, float r) {
	mavlink_msg_attitude_pack(mySystemId,myComponentId,&msg,getTime_ms(),roll,pitch,yaw,p,q,r);
	return sendMessage();
}
/* Attitude Getter */
bool MAVLink::getAttitude(float &roll, float &pitch, float &yaw, float &p, float &q, float &r) {
	MAVLinkMessage * mm = &MessageMap[MAVLINK_MSG_ID_ATTITUDE];
	if (mm == NULL) {
		return false;
	}
	roll = mavlink_msg_attitude_get_roll(&mm->msg);
	pitch = mavlink_msg_attitude_get_pitch(&mm->msg);
	yaw = mavlink_msg_attitude_get_yaw(&mm->msg);
	p = mavlink_msg_attitude_get_rollspeed(&mm->msg);
	q = mavlink_msg_attitude_get_pitchspeed(&mm->msg);
	r = mavlink_msg_attitude_get_yawspeed(&mm->msg);
	return checkTimeout(mm,MAVLINK_ATTITUDE_TIMEOUT);
}

/* RC Override Sender */
bool MAVLink::sendRCOverride(uint16_t c1, uint16_t c2, uint16_t c3, uint16_t c4, uint16_t c5, uint16_t c6, uint16_t c7, uint16_t c8) {
	mavlink_msg_rc_channels_override_pack(mySystemId,myComponentId,&msg,targetSystemId,targetComponentId,c1,c2,c3,c4,c5,c6,c7,c8);
	return sendMessage();
}

/* RC Override Getter */
bool MAVLink::getRCOverride(uint16_t &c1, uint16_t &c2, uint16_t &c3, uint16_t &c4, uint16_t &c5, uint16_t &c6, uint16_t &c7, uint16_t &c8) {
	MAVLinkMessage * mm = &MessageMap[MAVLINK_MSG_ID_RC_CHANNELS_OVERRIDE];
	if (mm == NULL) {
		return false;
	}
	c1 = mavlink_msg_rc_channels_override_get_chan1_raw(&mm->msg);
	c2 = mavlink_msg_rc_channels_override_get_chan2_raw(&mm->msg);
	c3 = mavlink_msg_rc_channels_override_get_chan3_raw(&mm->msg);
	c4 = mavlink_msg_rc_channels_override_get_chan4_raw(&mm->msg);
	c5 = mavlink_msg_rc_channels_override_get_chan5_raw(&mm->msg);
	c6 = mavlink_msg_rc_channels_override_get_chan6_raw(&mm->msg);
	c7 = mavlink_msg_rc_channels_override_get_chan7_raw(&mm->msg);
	c8 = mavlink_msg_rc_channels_override_get_chan8_raw(&mm->msg);
	return checkTimeout(mm,MAVLINK_RC_OVERRIDE_TIMEOUT);
}

/* Raw GPS Sender */
bool MAVLink::sendRawGPS(int fix, float lat, float lng, float alt, float eph, float epv, float v, float crs) {
	mavlink_msg_gps_raw_pack(mySystemId,myComponentId,&msg,getTime_ms(),fix,lat,lng,alt,eph,epv,v,crs);
	return sendMessage();
}

/* Raw GPS Getter */
bool MAVLink::getRawGPS(int &fix, float &lat, float &lng, float &alt, float &eph, float &epv, float &v, float &crs) {
	MAVLinkMessage * mm = &MessageMap[MAVLINK_MSG_ID_GPS_RAW];
	if (mm == NULL) {
		return false;
	}
	fix = mavlink_msg_gps_raw_get_fix_type(&mm->msg);
	lat = mavlink_msg_gps_raw_get_lat(&mm->msg);
	lng = mavlink_msg_gps_raw_get_lon(&mm->msg);
	alt = mavlink_msg_gps_raw_get_alt(&mm->msg);
	eph = mavlink_msg_gps_raw_get_eph(&mm->msg);
	epv = mavlink_msg_gps_raw_get_epv(&mm->msg);
	v = mavlink_msg_gps_raw_get_v(&mm->msg);
	crs = mavlink_msg_gps_raw_get_hdg(&mm->msg);
	return checkTimeout(mm,MAVLINK_RAW_GPS_TIMEOUT);
}

/* VFR HUD Sender */
bool MAVLink::sendVFRHUD(float airspeed, float groundspeed, int16_t heading, uint16_t throttle, float alt, float climb) {
	mavlink_msg_vfr_hud_pack(mySystemId,myComponentId,&msg,airspeed,groundspeed,heading,throttle,alt,climb);
	return sendMessage();
}

/* VFR HUD Getter */
bool MAVLink::getVFRHUD(float &airspeed, float &groundspeed, int16_t &heading, uint16_t &throttle, float &alt, float &climb) {
	MAVLinkMessage * mm = &MessageMap[MAVLINK_MSG_ID_VFR_HUD];
	if (mm == NULL) {
		return false;
	}
	airspeed = mavlink_msg_vfr_hud_get_airspeed(&mm->msg);
	groundspeed = mavlink_msg_vfr_hud_get_groundspeed(&mm->msg);
	heading = mavlink_msg_vfr_hud_get_heading(&mm->msg);
	throttle = mavlink_msg_vfr_hud_get_throttle(&mm->msg);
	alt = mavlink_msg_vfr_hud_get_alt(&mm->msg);
	climb = mavlink_msg_vfr_hud_get_climb(&mm->msg);
	return checkTimeout(mm,MAVLINK_VFR_HUD_TIMEOUT);
}