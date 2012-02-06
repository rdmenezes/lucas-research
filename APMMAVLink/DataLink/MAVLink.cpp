#include "MAVLink.h"

std::map<std::string, MAVLinkMessage> MAVLink::MessageMapIn;
std::map<std::string, MAVLinkMessage> MAVLink::MessageMapOut;

/* Constructor for the MAVLink class
 *	Takes the id's of this system and component and a pointer to the datalink to be used
 */
MAVLink::MAVLink(uint8_t mySystemId, uint8_t myComponentId, DataLink *link) {
	this->mySystemId = mySystemId;
	this->myComponentId = myComponentId;
	this->targetSystemId = -1;
	this->targetComponentId = -1;
	this->link = link;
    this->lastSendTime = 0;
	this->overflow = 0;
}

/* Set the id of the component to which messages should be sent
 *	Note this is not implemented on a lot of messages, see the MAVLink documentation
 *	to figure out which ones
 */
void MAVLink::setTargetComponent(uint8_t targetSystemId, uint8_t targetComponentId) {
	this->targetSystemId = targetSystemId;
	this->targetComponentId = targetComponentId;
}


int MAVLink::getTargetComponent() {
	return targetComponentId;
}
int MAVLink::getTargetSystem() {
	return targetSystemId;
}

bool MAVLink::getIDFromHeartbeat() {
	std::map<std::string,MAVLinkMessage>::iterator it;
	for (int i = 0; i<1000; i++) {
		receiveMessage();
		for (it = MessageMapIn.begin(); it != MessageMapIn.end(); it++) {
			int s, c, k = -1;
			sscanf((it->first).c_str(),"%d:%d %d", &s, &c, &k);
			if (k == 0) {
				this->targetSystemId = s;
				this->targetComponentId = c;
				return true;
			}
		}
		Sleep(10);
	}

	this->targetSystemId = -1;
	this->targetComponentId = -1;
	return false;
}

/* Receive a message from the DataLink
 *	This stores the latest message received for use by the getters
 *	This function should be called at least once per loop to ensure all packets
 *	get captured. If running on a PC you should consider threading a call to this
 *	function so it is called regularly in the background
 */
int MAVLink::receiveMessage() {
	mavlink_message_t msg;
	mavlink_status_t status;
	uint8_t buffer[MAVLINK_BUFFER_SIZE];
	memcpy(buffer,overBuffer,overflow);
	if (link == NULL) { return -1; }
	int msg_len = link->receive(MAVLINK_BUFFER_SIZE,(char*)(buffer+overflow));
	int j = 0;
	int k = 0;
	for (int i=0; i<(msg_len+overflow); i++) {
		if (mavlink_parse_char(0,buffer[i],&msg,&status)) {
			addMessage(msg);
			memset(&msg,'\0',sizeof(mavlink_message_t));
			memset(&status,'\0',sizeof(mavlink_status_t));
			j++;
			k = i;
		}
	}
/*	if (k<msg_len) {
		memset(overBuffer,'\0',MAVLINK_BUFFER_SIZE);
		memcpy(overBuffer,buffer+k+1,msg_len-k-1);
		overflow = msg_len-k-1;
	} else {*/
		overflow = 0;
	//}
	return j;
}

MAVLinkMessage * MAVLink::findMessage(int id) {
	char key[16];
	sprintf(key,"%d:%d %d", targetSystemId, targetComponentId, id);
	if (MessageMapIn.find(key) != MessageMapIn.end()) {
		return &MessageMapIn[key];
	} else {
		return NULL;
	}
}

/* Add the latest packet to local storage, overriding previous examples
 *	Time of receipt is captured to allow the timeout conditions to be
 *	evaluated by the getters
 */
void MAVLink::addMessage(mavlink_message_t &msg) {
	MAVLinkMessage mm;
	mm.msg = msg;
	mm.timeReceived = getTime_ms();
	char key[16];
	sprintf(key,"%d:%d %d", msg.sysid, msg.compid, msg.msgid);
	MessageMapIn[key] = mm;
}

/* Send a message
 *	Once the buffer has been filled by a sender this function is called
 *	to send it to the DataLink.
 *	Returns true if successful, false otherwise
 */
bool MAVLink::sendMessage(mavlink_message_t &msg) {
    MAVLinkMessage mm;
    mm.msg = msg;
    mm.timeReceived = getTime_ms();
	char key[16];
    sprintf(key,"%d:%d %d", targetSystemId, targetComponentId, msg.msgid);
    MessageMapOut[key] = mm;
    return true;//sendMessages();
}


int MAVLink::sendMessages() {
    if (getTime_ms() < lastSendTime + SEND_RATE) {
        return -1;
    }
    uint8_t buffer[MAVLINK_BUFFER_SIZE];
	if (link == NULL) { return -2; }
    
    std::map<std::string, MAVLinkMessage>::iterator it;
    std::string key;
    long earliestTime = -1;
    for ( it=MessageMapOut.begin() ; it != MessageMapOut.end(); it++ ) {
        if (earliestTime == -1 || (it->second).timeReceived < earliestTime) {
            key = it->first;
            earliestTime = (it->second).timeReceived;
        }
    }
    if (earliestTime == -1) { return MessageMapOut.size();}
	int msg_len = mavlink_msg_to_send_buffer(buffer, &(MessageMapOut[key].msg));
    lastSendTime = getTime_ms();
    int id = (MessageMapOut[key].msg).msgid;
    MessageMapOut.erase(key);
    int ret = id*link->send((char *)buffer, msg_len);
	return ret;
}

/* Get the time (Milliseconds since midnight)
 *	TODO: update this to the UNIX epoch
 */
long MAVLink::getTime_ms() {
#ifdef _WIN32
	SYSTEMTIME st;
	GetSystemTime(&st);
    return st.wMilliseconds
		+ st.wSecond*1000
		+ st.wMinute*1000*60
		+ st.wHour*1000*60*60;
#elif __linux__
	timeval tim;
	gettimeofday(&tim, NULL);
        return (long)(tim.tv_sec*1000+(tim.tv_usec/1000));
#endif
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
	mavlink_message_t msg;
	mavlink_msg_heartbeat_pack(mySystemId,myComponentId,&msg,type,autopilotType);
	return sendMessage(msg);
}

/* Attitude Sender */
bool MAVLink::sendAttitude(float roll, float pitch, float yaw, float p, float q, float r) {
	mavlink_message_t msg;
	mavlink_msg_attitude_pack(mySystemId,myComponentId,&msg,getTime_ms(),roll,pitch,yaw,p,q,r);
	return sendMessage(msg);
}
/* Attitude Getter */
bool MAVLink::getAttitude(float &roll, float &pitch, float &yaw, float &p, float &q, float &r) {
	MAVLinkMessage * mm = findMessage(MAVLINK_MSG_ID_ATTITUDE);
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
	mavlink_message_t msg;
	mavlink_msg_rc_channels_override_pack(mySystemId,myComponentId,&msg,targetSystemId,targetComponentId,c1,c2,c3,c4,c5,c6,c7,c8);
	return sendMessage(msg);
}

/* RC Override Getter */
bool MAVLink::getRCOverride(uint16_t &c1, uint16_t &c2, uint16_t &c3, uint16_t &c4, uint16_t &c5, uint16_t &c6, uint16_t &c7, uint16_t &c8) {
	MAVLinkMessage * mm = findMessage(MAVLINK_MSG_ID_RC_CHANNELS_OVERRIDE);
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
	mavlink_message_t msg;
	mavlink_msg_gps_raw_pack(mySystemId,myComponentId,&msg,getTime_ms(),fix,lat,lng,alt,eph,epv,v,crs);
	return sendMessage(msg);
}

/* Raw GPS Getter */
bool MAVLink::getRawGPS(int &fix, float &lat, float &lng, float &alt, float &eph, float &epv, float &v, float &crs) {
	MAVLinkMessage * mm = findMessage(MAVLINK_MSG_ID_GPS_RAW);
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

bool MAVLink::sendGlobalPositionInt(int32_t lat, int32_t lng, int32_t alt, int16_t vx, int16_t vy, int16_t vz) {
	mavlink_message_t msg;
	mavlink_msg_global_position_int_pack(mySystemId,myComponentId,&msg,lat,lng,alt,vx,vy,vz);
	return sendMessage(msg);
}
bool MAVLink::getGlobalPositionInt(int32_t &lat, int32_t &lng, int32_t &alt, int16_t &vx, int16_t &vy, int16_t &vz) {
	MAVLinkMessage * mm = findMessage(MAVLINK_MSG_ID_GLOBAL_POSITION_INT);
	if (mm == NULL) {
		return false;
	}
	lat = mavlink_msg_global_position_int_get_lat(&mm->msg);
	lng = mavlink_msg_global_position_int_get_lon(&mm->msg);
	alt = mavlink_msg_global_position_int_get_alt(&mm->msg);
	vx = mavlink_msg_global_position_int_get_vx(&mm->msg);
	vy = mavlink_msg_global_position_int_get_vy(&mm->msg);
	vz = mavlink_msg_global_position_int_get_vz(&mm->msg);
	
	return checkTimeout(mm,MAVLINK_RAW_GPS_TIMEOUT);
}



/* VFR HUD Sender */
bool MAVLink::sendVFRHUD(float airspeed, float groundspeed, int16_t heading, uint16_t throttle, float alt, float climb) {
	mavlink_message_t msg;
	mavlink_msg_vfr_hud_pack(mySystemId,myComponentId,&msg,airspeed,groundspeed,heading,throttle,alt,climb);
	return sendMessage(msg);
}

/* VFR HUD Getter */
bool MAVLink::getVFRHUD(float &airspeed, float &groundspeed, int16_t &heading, uint16_t &throttle, float &alt, float &climb) {
	MAVLinkMessage * mm = findMessage(MAVLINK_MSG_ID_VFR_HUD);
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

/* Raw Servo Output Sender */
bool MAVLink::sendRawServos(uint16_t s1, uint16_t s2, uint16_t s3, uint16_t s4, uint16_t s5, uint16_t s6, uint16_t s7, uint16_t s8) {
	mavlink_message_t msg;
	mavlink_msg_servo_output_raw_pack(mySystemId,myComponentId,&msg,s1,s2,s3,s4,s5,s6,s7,s8);
	return sendMessage(msg);
}

/* Raw Servo Getter */
bool MAVLink::getRawServos(uint16_t &s1, uint16_t &s2, uint16_t &s3, uint16_t &s4, uint16_t &s5, uint16_t &s6, uint16_t &s7, uint16_t &s8) {
	MAVLinkMessage * mm = findMessage(MAVLINK_MSG_ID_SERVO_OUTPUT_RAW);
	if (mm == NULL) {
		return false;
	}
	s1 = mavlink_msg_servo_output_raw_get_servo1_raw(&mm->msg);
	s2 = mavlink_msg_servo_output_raw_get_servo2_raw(&mm->msg);
	s3 = mavlink_msg_servo_output_raw_get_servo3_raw(&mm->msg);
	s4 = mavlink_msg_servo_output_raw_get_servo4_raw(&mm->msg);
	s5 = mavlink_msg_servo_output_raw_get_servo5_raw(&mm->msg);
	s6 = mavlink_msg_servo_output_raw_get_servo6_raw(&mm->msg);
	s7 = mavlink_msg_servo_output_raw_get_servo7_raw(&mm->msg);
	s8 = mavlink_msg_servo_output_raw_get_servo8_raw(&mm->msg);
	return checkTimeout(mm,MAVLINK_SERVO_TIMEOUT);
}

/* Raw Servo Output Sender */
bool MAVLink::sendScaledServos(int16_t s1, int16_t s2, int16_t s3, int16_t s4, int16_t s5, int16_t s6, int16_t s7, int16_t s8, uint8_t rssi) {
	mavlink_message_t msg;
	mavlink_msg_rc_channels_scaled_pack(mySystemId,myComponentId,&msg,s1,s2,s3,s4,s5,s6,s7,s8,rssi);
	return sendMessage(msg);
}

/* Raw Servo Getter */
bool MAVLink::getScaledServos(int16_t &s1, int16_t &s2, int16_t &s3, int16_t &s4, int16_t &s5, int16_t &s6, int16_t &s7, int16_t &s8, uint8_t &rssi) {
	MAVLinkMessage * mm = findMessage(MAVLINK_MSG_ID_RC_CHANNELS_SCALED);
	if (mm == NULL) {
		return false;
	}
	s1 = mavlink_msg_rc_channels_scaled_get_chan1_scaled(&mm->msg);
	s2 = mavlink_msg_rc_channels_scaled_get_chan2_scaled(&mm->msg);
	s3 = mavlink_msg_rc_channels_scaled_get_chan3_scaled(&mm->msg);
	s4 = mavlink_msg_rc_channels_scaled_get_chan4_scaled(&mm->msg);
	s5 = mavlink_msg_rc_channels_scaled_get_chan5_scaled(&mm->msg);
	s6 = mavlink_msg_rc_channels_scaled_get_chan6_scaled(&mm->msg);
	s7 = mavlink_msg_rc_channels_scaled_get_chan7_scaled(&mm->msg);
	s8 = mavlink_msg_rc_channels_scaled_get_chan8_scaled(&mm->msg);
	return checkTimeout(mm,MAVLINK_SERVO_TIMEOUT);
}

/* Mode Sender */
bool MAVLink::sendMode(uint32_t mode) {
	mavlink_message_t msg;
	mavlink_msg_set_mode_pack(mySystemId,myComponentId,&msg,targetSystemId,mode);
	return sendMessage(msg);
}

/* Mode Getter */
bool MAVLink::getMode(uint32_t &mode) {
	MAVLinkMessage * mm = findMessage(MAVLINK_MSG_ID_SET_MODE);
	if (mm == NULL) {
		return false;
	}
	mode = mavlink_msg_set_mode_get_mode(&mm->msg);
	return checkTimeout(mm,MAVLINK_MODE_TIMEOUT);
}

/* Attitude Command Sender */
bool MAVLink::sendAttitudeCommand(float roll, float pitch, float yaw, float thrust) {
	mavlink_message_t msg;
	mavlink_msg_set_roll_pitch_yaw_thrust_pack(mySystemId,myComponentId,&msg,targetSystemId,targetComponentId,roll,pitch,yaw,thrust);
	return sendMessage(msg);
}
/* Attitude Command Getter */
bool MAVLink::getAttitudeCommand(float &roll, float &pitch, float &yaw, float &thrust) {
	MAVLinkMessage * mm = findMessage(MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST);
	if (mm == NULL) {
		return false;
	}
	roll = mavlink_msg_set_roll_pitch_yaw_thrust_get_roll(&mm->msg);
	pitch = mavlink_msg_set_roll_pitch_yaw_thrust_get_pitch(&mm->msg);
	yaw = mavlink_msg_set_roll_pitch_yaw_thrust_get_yaw(&mm->msg);
	thrust = mavlink_msg_set_roll_pitch_yaw_thrust_get_thrust(&mm->msg);
	return checkTimeout(mm,MAVLINK_ATTITUDE_TIMEOUT);
}

bool MAVLink::sendRequestStream(uint8_t streamId, uint16_t steamRate, uint8_t startStop) {
	mavlink_message_t msg;
	mavlink_msg_request_data_stream_pack(mySystemId, myComponentId, &msg, targetSystemId, targetComponentId, streamId, steamRate, startStop);
	return sendMessage(msg);
}

bool MAVLink::sendSystemStatus(uint8_t mode, uint8_t nav_mode, uint8_t status, uint16_t load, uint16_t vbat, uint16_t battery_remaining, uint16_t packet_drop) {
    mavlink_message_t msg;
    mavlink_msg_sys_status_pack(mySystemId,myComponentId,&msg, mode, nav_mode, status, load, vbat, battery_remaining, packet_drop);
    return sendMessage(msg);
}
bool MAVLink::getSystemStatus(uint8_t &mode, uint8_t &nav_mode, uint8_t &status, uint16_t &load, uint16_t &vbat, uint16_t &battery_remaining, uint16_t &packet_drop) {
    MAVLinkMessage * mm = findMessage(MAVLINK_MSG_ID_SYS_STATUS);
	if (mm == NULL) {
		return false;
	}
    mode = mavlink_msg_sys_status_get_mode(&mm->msg);
    nav_mode = mavlink_msg_sys_status_get_nav_mode(&mm->msg);
    status = mavlink_msg_sys_status_get_status(&mm->msg);
    load = mavlink_msg_sys_status_get_load(&mm->msg);
    vbat = mavlink_msg_sys_status_get_vbat(&mm->msg);
    battery_remaining = mavlink_msg_sys_status_get_battery_remaining(&mm->msg);
    packet_drop = mavlink_msg_sys_status_get_packet_drop(&mm->msg);
    return checkTimeout(mm,MAVLINK_STATUS_TIMEOUT);
}