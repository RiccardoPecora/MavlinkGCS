#include "Mavlink_8.h"

//#define DEBUG

MAVLINK::GCS_Mavlink::GCS_Mavlink(mutex& _m_cout)
    : m_cout(_m_cout) {

}


void MAVLINK::GCS_Mavlink::mav_request_data(uint8_t _enable, int16_t _rateHz, uint16_t &len, uint8_t buf[]) {
	mavlink_message_t msg;
	//uint8_t buf[MAVLINK_MAX_PACKET_LEN];

	// STREAMS that can be requested
	/*
	 * Definitions are in common.h: enum MAV_DATA_STREAM
	 *
	 * MAV_DATA_STREAM_ALL=0, // Enable all data streams
	 * MAV_DATA_STREAM_RAW_SENSORS=1, /* Enable IMU_RAW, GPS_RAW, GPS_STATUS packets.
	 * MAV_DATA_STREAM_EXTENDED_STATUS=2, /* Enable GPS_STATUS, CONTROL_STATUS, AUX_STATUS
	 * MAV_DATA_STREAM_RC_CHANNELS=3, /* Enable RC_CHANNELS_SCALED, RC_CHANNELS_RAW, SERVO_OUTPUT_RAW
	 * MAV_DATA_STREAM_RAW_CONTROLLER=4, /* Enable ATTITUDE_CONTROLLER_OUTPUT, POSITION_CONTROLLER_OUTPUT, NAV_CONTROLLER_OUTPUT.
	 * MAV_DATA_STREAM_POSITION=6, /* Enable LOCAL_POSITION, GLOBAL_POSITION/GLOBAL_POSITION_INT messages.
	 * MAV_DATA_STREAM_EXTRA1=10, /* Dependent on the autopilot
	 * MAV_DATA_STREAM_EXTRA2=11, /* Dependent on the autopilot
	 * MAV_DATA_STREAM_EXTRA3=12, /* Dependent on the autopilot
	 * MAV_DATA_STREAM_ENUM_END=13,
	 *
	 * Data in PixHawk available in:
	 *  - Battery, amperage and voltage (SYS_STATUS) in MAV_DATA_STREAM_EXTENDED_STATUS
	 *  - Gyro info (IMU_SCALED) in MAV_DATA_STREAM_EXTRA1
	 */

	 // To be setup according to the needed information to be requested from the Pixhawk
	//const int  maxStreams = 2;
	//const uint8_t MAVStreams[maxStreams] = { MAV_DATA_STREAM_EXTENDED_STATUS, MAV_DATA_STREAM_EXTRA1 };
	//const uint16_t MAVRates[maxStreams] = { 0x02,0x05 };

	const int  maxStreams = 1;
	const uint8_t MAVStreams[maxStreams] = { MAV_DATA_STREAM_ALL };
	const int16_t MAVRates[maxStreams] = { _rateHz };

	for (int i = 0; i < maxStreams; i++) {
		/*
		 * mavlink_msg_request_data_stream_pack(system_id, component_id,
		 *    &msg,
		 *    target_system, target_component,
		 *    MAV_DATA_STREAM_POSITION, 10000000, 1);
		 *
		 * mavlink_msg_request_data_stream_pack(uint8_t system_id, uint8_t component_id,
		 *    mavlink_message_t* msg,
		 *    uint8_t target_system, uint8_t target_component, uint8_t req_stream_id,
		 *    uint16_t req_message_rate, uint8_t start_stop)
		 *
		 */
		mavlink_msg_request_data_stream_pack(1, 255, &msg, 1, 0, MAVStreams[i], MAVRates[i], _enable);
        len = mavlink_msg_to_send_buffer(buf, &msg);
		
	}
}

void MAVLINK::GCS_Mavlink::mav_msg_parse(uint8_t chan, uint8_t* read_buf,
                                         uint16_t &read_buf_len, mavlink_message_t &msg,
                                         mavlink_status_t &status) {

    for (uint16_t i = 0; i < read_buf_len; i++) {
        if (mavlink_parse_char(chan, (uint8_t)read_buf[i], &msg, &status)) {
            return;

        }
    }
}


void MAVLINK::GCS_Mavlink::send_mav_cmd_do_set_mode(COPTER_MODE _mode, uint16_t &len, uint8_t buf[]) {
	mavlink_command_long_t set_mode = { 0 };
	set_mode.target_system = 1;
	set_mode.target_component = 0;
	set_mode.command = MAV_CMD_DO_SET_MODE;		//176
	set_mode.confirmation = true;
	set_mode.param1 = 1; 				//need to be 1 ?? check			 	
	set_mode.param2 = _mode;	//guided_mode: 4 for drone / 15 for rover... 

	// Encode:
	mavlink_message_t msg;
	mavlink_msg_command_long_encode(1, 255, &msg, &set_mode);
    len = mavlink_msg_to_send_buffer(buf, &msg);
}

void MAVLINK::GCS_Mavlink::send_mav_cmd_component_arm(uint16_t &len, uint8_t buf[]) {
	mavlink_command_long_t arming = { 0 };
	arming.target_system = 1;
	arming.target_component = 0;
	arming.command = MAV_CMD_COMPONENT_ARM_DISARM;	//400
	arming.confirmation = true;
	arming.param1 = 1; 	//0: 0: disarm, 1: arm		 	
	arming.param2 = 0;	//0: arm-disarm unless prevented by safety checks (i.e. when landed), 21196: force arming/disarming (e.g. allow arming to override preflight checks and disarming in flight)

	// Encode:
	mavlink_message_t msg;
	mavlink_msg_command_long_encode(1, 255, &msg, &arming);
    len = mavlink_msg_to_send_buffer(buf, &msg);

}

void MAVLINK::GCS_Mavlink::send_mav_cmd_component_disarm(uint16_t &len, uint8_t buf[]) {
	mavlink_command_long_t arming = { 0 };
	arming.target_system = 1;
	arming.target_component = 0;
	arming.command = MAV_CMD_COMPONENT_ARM_DISARM;	//400
	arming.confirmation = true;
	arming.param1 = 0; 	//0: 0: disarm, 1: arm		 	
	arming.param2 = 0;	//0: arm-disarm unless prevented by safety checks (i.e. when landed), 21196: force arming/disarming (e.g. allow arming to override preflight checks and disarming in flight)

	// Encode:
	mavlink_message_t msg;
	mavlink_msg_command_long_encode(1, 255, &msg, &arming);
    len = mavlink_msg_to_send_buffer(buf, &msg);

}

void MAVLINK::GCS_Mavlink::send_mav_cmd_nav_takeoff(float _alt, uint16_t &len, uint8_t buf[]) {
	mavlink_command_long_t takeoff;
	takeoff.target_system = 1;
	takeoff.target_component = 0;
	takeoff.command = MAV_CMD_NAV_TAKEOFF; //22
	takeoff.confirmation = true;
	takeoff.param1 = 0; //Minimum pitch (if airspeed sensor present), desired pitch without sensor [deg]
	takeoff.param2 = 0; //Empty
	takeoff.param3 = 0; //Empty
	takeoff.param4 = NAN; //Yaw angle (if magnetometer present), ignored without magnetometer. NaN to use the current system yaw heading mode (e.g. yaw towards next waypoint, yaw to home, etc.). [deg]
	takeoff.param5 = 0; //latitude (WGS84)
	takeoff.param6 = 0; //longitude (WGS84)
	takeoff.param7 = _alt; //altitude (MSL) [m]

	// Encode:
	mavlink_message_t msg;
	mavlink_msg_command_long_encode(1, 255, &msg, &takeoff);
    len = mavlink_msg_to_send_buffer(buf, &msg);

}

void MAVLINK::GCS_Mavlink::send_mav_cmd_nav_land(uint16_t &len, uint8_t buf[]) {
	mavlink_command_long_t land;
	land.target_system = 1;
	land.target_component = 0;
	land.command = MAV_CMD_NAV_LAND; //21
	land.confirmation = true;
	land.param1 = 0; //Minimum target altitude if landing is aborted (0 = undefined/use system default). [m]
	land.param2 = 0; //Precision land mode.
	land.param3 = 0; //Empty
	land.param4 = NAN; //Desired yaw angle. NaN to use the current system yaw heading mode (e.g. yaw towards next waypoint, yaw to home, etc.). [deg]
	land.param5 = 0; //latitude (WGS84)
	land.param6 = 0; //longitude (WGS84)
	land.param7 = 0; //Landing altitude (ground level in current frame). [m]

	// Encode:
	mavlink_message_t msg;
	mavlink_msg_command_long_encode(1, 255, &msg, &land);
    len = mavlink_msg_to_send_buffer(buf, &msg);
}

void MAVLINK::GCS_Mavlink::send_mav_cmd_do_reposition(uint32_t _lat, uint32_t _long, float _alt,
uint16_t &len, uint8_t buf[]) {
	mavlink_command_int_t cmd_reposition;
	cmd_reposition.command = MAV_CMD_DO_REPOSITION;
	cmd_reposition.target_system = 1;
	cmd_reposition.target_component = 0;
	cmd_reposition.frame = MAV_FRAME_GLOBAL_RELATIVE_ALT;
	cmd_reposition.param1 = 10.0; //Ground speed, less than 0 (-1) for default [m/s]
	cmd_reposition.param2 = 0; //Bitmask of option flags.
	cmd_reposition.param3 = 0; //Loiter radius for planes. Positive values only, direction is controlled by Yaw value. A value of zero or NaN is ignored. [m]
	cmd_reposition.param4 = NAN; //	Yaw heading. NaN to use the current system yaw heading mode (e.g. yaw towards next waypoint, yaw to home, etc.). For planes indicates loiter direction (0: clockwise, 1: counter clockwise)
	cmd_reposition.x = _lat; //latitude (WGS84)
	cmd_reposition.y = _long; //longitude (WGS84)
	cmd_reposition.z = _alt; //altitude (MSL)

	// Encode:
	mavlink_message_t msg;
	mavlink_msg_command_int_encode(1, 255, &msg, &cmd_reposition);
    len = mavlink_msg_to_send_buffer(buf, &msg);

}

void MAVLINK::GCS_Mavlink::send_mav_cmd_nav_rtl(uint16_t &len, uint8_t buf[]) {
	mavlink_command_long_t rtl;
	rtl.target_system = 1;
	rtl.target_component = 0;
	rtl.command = MAV_CMD_NAV_RETURN_TO_LAUNCH; //20
	rtl.confirmation = true;
	rtl.param1 = 0; //Empty
	rtl.param2 = 0; //Empty
	rtl.param3 = 0; //Empty
	rtl.param4 = 0; //Empty
	rtl.param5 = 0; //Empty
	rtl.param6 = 0; //Empty
	rtl.param7 = 0; //Empty

	// Encode:
	mavlink_message_t msg;
	mavlink_msg_command_long_encode(1, 255, &msg, &rtl);
    len = mavlink_msg_to_send_buffer(buf, &msg);
}

void MAVLINK::GCS_Mavlink::autopilot_reboot(uint16_t &len, uint8_t buf[]) {
	mavlink_command_long_t atp_reboot;
	atp_reboot.target_system = 1;
	atp_reboot.target_component = 0;
	atp_reboot.command = MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN; //246
	atp_reboot.confirmation = true;
	atp_reboot.param1 = 1; //Autopilot reboot
	atp_reboot.param2 = 0; //Empty
	atp_reboot.param3 = 0; //Empty
	atp_reboot.param4 = 0; //Empty
	atp_reboot.param5 = 0; //Empty
	atp_reboot.param6 = 0; //Empty
	atp_reboot.param7 = 0; //Empty

	// Encode:
	mavlink_message_t msg;
	mavlink_msg_command_long_encode(1, 255, &msg, &atp_reboot);
    len = mavlink_msg_to_send_buffer(buf, &msg);
}

void MAVLINK::GCS_Mavlink::add_mav_cmd_nav_waypoint_int(float _hold_time, float _acc_rad,
                                                        float _pass_rad, float _yaw, int32_t _lat,
                                                        int32_t _long, float _alt) {
	mavlink_mission_item_int_t cmd_add_waypoint;
	cmd_add_waypoint.command = MAV_CMD_NAV_WAYPOINT;
	cmd_add_waypoint.target_system = 1;
	cmd_add_waypoint.target_component = 0;
	cmd_add_waypoint.seq = miss_buf_wp.size();
	cmd_add_waypoint.frame = MAV_FRAME_GLOBAL_RELATIVE_ALT;
	cmd_add_waypoint.mission_type = MAV_MISSION_TYPE_MISSION;
	cmd_add_waypoint.current = 0;
	cmd_add_waypoint.autocontinue = 1;
	cmd_add_waypoint.param1 = _hold_time; //Hold time. (ignored by fixed wing, time to stay at waypoint for rotary wing) [s]
	cmd_add_waypoint.param2 = _acc_rad; //Accept Radius: Acceptance radius (if the sphere with this radius is hit, the waypoint counts as reached) [m]
	cmd_add_waypoint.param3 = _pass_rad; //Pass Radius:0 to pass through the WP, if > 0 radius to pass by WP. Positive value for clockwise orbit, negative value for counter-clockwise orbit. Allows trajectory control. [m]
	cmd_add_waypoint.param4 = _yaw; //Yaw: Desired yaw angle at waypoint (rotary wing). NaN to use the current system yaw heading mode (e.g. yaw towards next waypoint, yaw to home, etc.). [deg]
	cmd_add_waypoint.x = _lat; //latitude (WGS84) 
	cmd_add_waypoint.y = _long; //longitude (WGS84)
	cmd_add_waypoint.z = _alt; //altitude (MSL) [m]

	miss_buf_wp.push_back(cmd_add_waypoint);

}

void MAVLINK::GCS_Mavlink::upload_mission() {

    //send_mav_miss_count_msg(1, 0, MAV_MISSION_TYPE_MISSION, miss_buf_wp.size());
}

void MAVLINK::GCS_Mavlink::download_mission() {

    //send_mav_miss_req_list_msg(1, 0, MAV_MISSION_TYPE_MISSION);

}

void MAVLINK::GCS_Mavlink::clear_mission() {

	send_mav_miss_clear_msg(1, 0, MAV_MISSION_TYPE_MISSION);

}

void MAVLINK::GCS_Mavlink::abort_mission() {

    //send_mav_miss_ack_msg(1, 0, MAV_MISSION_TYPE::MAV_MISSION_TYPE_MISSION, MAV_MISSION_RESULT::MAV_MISSION_DENIED);

}

void MAVLINK::GCS_Mavlink::send_mav_miss_count_msg(uint8_t _target_system, uint8_t _target_component,
                                                   MAV_MISSION_TYPE _mission_type, uint16_t _count,
                                                   uint16_t &len, uint8_t buf[]) {

	mavlink_mission_count_t msg_miss_count;
	msg_miss_count.target_system = _target_system;
	msg_miss_count.target_component = _target_component;
	msg_miss_count.mission_type = _mission_type;
	msg_miss_count.count = _count;

	// Encode:
	mavlink_message_t msg;
	mavlink_msg_mission_count_encode(1, 255, &msg, &msg_miss_count);
    len = mavlink_msg_to_send_buffer(buf, &msg);

}

void MAVLINK::GCS_Mavlink::send_mav_miss_item_msg(mavlink_mission_item_int_t& _mission_item,
                                                  uint16_t &len, uint8_t buf[]) {
	mavlink_message_t msg;
	mavlink_msg_mission_item_int_encode(1, 255, &msg, &_mission_item);
    len = mavlink_msg_to_send_buffer(buf, &msg);
}

void MAVLINK::GCS_Mavlink::send_mav_miss_req_list_msg(uint8_t _target_system, uint8_t _target_component,
                                                      MAV_MISSION_TYPE _mission_type, uint16_t &len,
                                                      uint8_t buf[]) {

	mavlink_mission_request_list_t msg_miss_req_lst;
	msg_miss_req_lst.target_system = _target_system;
	msg_miss_req_lst.target_component = _target_component;
	msg_miss_req_lst.mission_type = _mission_type;

	// Encode:
	mavlink_message_t msg;
	mavlink_msg_mission_request_list_encode(1, 255, &msg, &msg_miss_req_lst);
    len = mavlink_msg_to_send_buffer(buf, &msg);

}

void MAVLINK::GCS_Mavlink::send_mav_miss_clear_msg(uint8_t _target_system, uint8_t _target_component, MAV_MISSION_TYPE _mission_type) {

	miss_buf_wp.clear();
	miss_recv_buf_wp.clear();

}

void MAVLINK::GCS_Mavlink::send_mav_miss_req_int_msg(uint8_t _target_system, uint8_t _target_component,
                                                     MAV_MISSION_TYPE _mission_type, uint16_t _seq,
                                                     uint16_t &len, uint8_t buf[]) {

	//Send Mav Request Int
	mavlink_mission_request_int_t miss_req;
	miss_req.target_system = _target_system;
	miss_req.target_component = _target_component;
	miss_req.mission_type = _mission_type;
	miss_req.seq = _seq;

	// Encode:
	mavlink_message_t msg;
	mavlink_msg_mission_request_int_encode(1, 255, &msg, &miss_req);
    len = mavlink_msg_to_send_buffer(buf, &msg);

}

void MAVLINK::GCS_Mavlink::send_mav_miss_ack_msg(uint8_t _target_system, uint8_t _target_component,
                                                 MAV_MISSION_TYPE _mission_type,
                                                 MAV_MISSION_RESULT _type, uint16_t &len, uint8_t buf[]) {

	//Send Mission Ack
	mavlink_mission_ack_t miss_ack;
	miss_ack.target_system = _target_system;
	miss_ack.target_component = _target_component;
	miss_ack.mission_type = _mission_type;
	miss_ack.type = _type; // MAV_MISSION_ACCEPTED;

	// Encode:
	mavlink_message_t msg;
	mavlink_msg_mission_ack_encode(1, 255, &msg, &miss_ack);
    len = mavlink_msg_to_send_buffer(buf, &msg);

}

void MAVLINK::GCS_Mavlink::populate_wp_buf(uint8_t _nWP) {
	for (uint8_t i = 0; i < _nWP; i++) {
		add_mav_cmd_nav_waypoint_int(
									(float)(i + 1),
									(float)(i + 1),
									(float)(i + 1),
									0.0,
									(-350000000 - i),
									(1490000000 + i),
									(10.0 + (float)(i))
		);
	}
}

void MAVLINK::GCS_Mavlink::show_wp_write_buf() {
	if (m_cout.try_lock()) {	
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "MISSION WP WRITE BUFFER" << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		for (mavlink_mission_item_int_t itm : miss_buf_wp) {
			cout << "Target system: " << to_string(itm.target_system) << endl;
			cout << "Target component: " << to_string(itm.target_component) << endl;
			cout << "Seq: " << to_string(itm.seq) << endl;
			cout << "Frame: " << to_string(itm.frame) << endl;
			cout << "Command: " << to_string(itm.command) << endl;
			cout << "Current: " << to_string(itm.current) << endl;
			cout << "Auto-continue: " << to_string(itm.autocontinue) << endl;
			cout << "Param 1: " << to_string(itm.param1) << endl;
			cout << "Param 2: " << to_string(itm.param2) << endl;
			cout << "Param 3: " << to_string(itm.param3) << endl;
			cout << "Param 4: " << to_string(itm.param4) << endl;
			cout << "X: " << to_string(itm.x) << endl;
			cout << "Y: " << to_string(itm.y) << endl;
			cout << "Z: " << to_string(itm.z) << endl;
			cout << "----------------------" << endl;
		}
		cout << endl;
		cout << endl;
		m_cout.unlock();
	}

}

void MAVLINK::GCS_Mavlink::show_wp_read_buf() {
	if (m_cout.try_lock()) {
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "MISSION WP READ BUFFER" << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		for (mavlink_mission_item_int_t itm : miss_recv_buf_wp) {
			cout << "Target system: " << to_string(itm.target_system) << endl;
			cout << "Target component: " << to_string(itm.target_component) << endl;
			cout << "Seq: " << to_string(itm.seq) << endl;
			cout << "Frame: " << to_string(itm.frame) << endl;
			cout << "Command: " << to_string(itm.command) << endl;
			cout << "Current: " << to_string(itm.current) << endl;
			cout << "Auto-continue: " << to_string(itm.autocontinue) << endl;
			cout << "Param 1: " << to_string(itm.param1) << endl;
			cout << "Param 2: " << to_string(itm.param2) << endl;
			cout << "Param 3: " << to_string(itm.param3) << endl;
			cout << "Param 4: " << to_string(itm.param4) << endl;
			cout << "X: " << to_string(itm.x) << endl;
			cout << "Y: " << to_string(itm.y) << endl;
			cout << "Z: " << to_string(itm.z) << endl;
			cout << "----------------------" << endl;
		}
		cout << endl;
		cout << endl;
		m_cout.unlock();
	}

}

void MAVLINK::GCS_Mavlink::send_test_ric_msg(uint16_t _id, int16_t _val, uint16_t &len, uint8_t buf[]) {
	//Send 
	mavlink_test_ric_msg_t test_ric;
	test_ric.id = _id;
	test_ric.TEST_RIC_value = _val;

	// Encode:
	mavlink_message_t msg;
	mavlink_msg_test_ric_msg_encode(1, 255, &msg, &test_ric);
    len = mavlink_msg_to_send_buffer(buf, &msg);

}
