#include "MAVLink.h"

MAVLink::MAVLink(uint8_t mySystemId, uint8_t myComponentId, DataLink *link) {
	this->mySystemId = mySystemId;
	this->myComponentId = myComponentId;
	this->link = link;
}

void MAVLink::setTargetComponent(uint8_t targetSystemId, uint8_t targetComponentId) {
	this->targetSystemId = targetSystemId;
	this->targetComponentId = targetComponentId;
}

bool MAVLink::receiveMessage() {
	int msg_len = link->receive(MAVLINK_BUFFER_SIZE,(char*)buffer);
	for (int i=0; i<msg_len; i++) {
		if (mavlink_parse_char(0,buffer[i],&msg,&status)) {
			MAVLinkMessage mm;
			mm.msg = msg;
			mm.timeReceived = getTime_ms();
			MessageMap[msg.msgid] = mm;

			return true;
		}
	}
	return false;
}

bool MAVLink::sendMessage() {
	int msg_len = mavlink_msg_to_send_buffer(buffer, &msg);
	return link->send((char *)buffer, msg_len);
}

int MAVLink::getTime_ms() {
	SYSTEMTIME st;
	GetSystemTime(&st);
    return st.wMilliseconds
		+ st.wSecond*1000
		+ st.wMinute*1000*60
		+ st.wHour*1000*60*60;
}

bool MAVLink::checkTimeout(MAVLinkMessage *mm, int timeout) {
	if ((getTime_ms()-mm->timeReceived)<timeout) {
		return true;
	}
	return false;
}







bool MAVLink::sendHeartbeat(uint8_t type, uint8_t autopilotType) {
	mavlink_msg_heartbeat_pack(mySystemId,myComponentId,&msg,type,autopilotType);
	return sendMessage();
}

bool MAVLink::sendAttitude(float roll, float pitch, float yaw, float p, float q, float r) {
	mavlink_msg_attitude_pack(mySystemId,myComponentId,&msg,getTime_ms(),roll,pitch,yaw,p,q,r);
	return sendMessage();
}

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

bool MAVLink::sendRCOverride(uint16_t c1, uint16_t c2, uint16_t c3, uint16_t c4, uint16_t c5, uint16_t c6, uint16_t c7, uint16_t c8) {
	mavlink_msg_rc_channels_override_pack(mySystemId,myComponentId,&msg,targetSystemId,targetComponentId,c1,c2,c3,c4,c5,c6,c7,c8);
	return sendMessage();
}
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