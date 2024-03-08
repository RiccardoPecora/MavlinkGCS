#ifndef Mavlink_h
#define Mavlink_h

#include <iostream>
#include <string.h>
#include <stdint.h>
#include <chrono>
#include <vector>
#include <thread>
#include <string>
#include <mutex>
//#include "common/mavlink.h"
//#include "ardupilotmega/mavlink.h"
#include "mavlink_ric/v2.0/ardupilotmega/mavlink.h"


using namespace std;


namespace MAVLINK {
/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
ENUMERATOR
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
enum CMD_ENUM {
	EXIT = 0,
	CONNECT,
	DISCONNECT,
	CHANGE_MODE,
	ARM,
	DISARM,
	TAKEOFF,
	LAND,
	GOTO,
	RTL,
	ADD_WAYPOINT,
	CLEAR_MISSION,
	UPLOAD_MISSION,
	DOWNLOAD_MISSION,
	ABORT_MISSION,
	AUTOPILOT_REBOOT,
	ENABLE_DISABLE_MAV_STREAM,
	POPULATE_WP_BUFFER,
	SHOW_WP_WRITE_BUFFER,
	SHOW_WP_READ_BUFFER,
	ENABLE_DISABLE_RECV_THREAD,
	SEND_TEST_RIC_MSG
};

enum MAV_MISS_UPLOAD_STATE {
	UPLOAD_IDLE = 0,
	SEND_MISSION_COUNT,
	TOUT_MISSION_COUNT,
	SEND_MISSION_ITEM,
	MISSION_ACK
};

enum MAV_MISS_DOWNLOAD_STATE {
	DOWNLOAD_IDLE = 0,
	SEND_MISSION_REQ_LIST,
	TOUT_MISSION_REQ_LIST,
	SEND_MISSION_REQ_INT,
	SEND_MISSION_ACK
};


/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
VARIABLES
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

static string cmd_str[50]{ "EXIT",
					"CONNECT",
					"DISCONNECT",
					"CHANGE_MODE",
					"ARM",
					"DISARM",
					"TAKEOFF",
					"LAND",
					"GOTO",
					"RTL",
					"ADD_WAYPOINT",
					"CLEAR_MISSION",
					"UPLOAD_MISSION",
					"DOWNLOAD_MISSION",
					"ABORT_MISSION",
					"AUTOPILOT_REBOOT",
					"ENABLE_DISABLE_MAV_STREAM",
					"POPULATE_WP_BUFFER",
					"SHOW_WP_WRITE_BUFFER",
					"SHOW_WP_READ_BUFFER",
					"ENABLE_DISABLE_RECV_THREAD",
					"SEND_TEST_RIC_MSG"
};



    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //CLASS
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    class GCS_Mavlink {

    public:
        GCS_Mavlink(mutex& _m_cout);
        void mav_request_data(uint8_t _enable, int16_t _rateHz, uint16_t &len, uint8_t buf[]);
        void mav_msg_parse(uint8_t chan,uint8_t* read_buf, uint16_t &read_buf_len,
                           mavlink_message_t &msg, mavlink_status_t &status);
        void send_mav_cmd_do_reposition(uint32_t _lat, uint32_t _long, float _alt, uint16_t &len, uint8_t buf[]);
        void send_mav_cmd_do_set_mode(COPTER_MODE _mode, uint16_t &len, uint8_t buf[]);
        void send_mav_cmd_component_arm(uint16_t &len, uint8_t buf[]);
        void send_mav_cmd_component_disarm(uint16_t &len, uint8_t buf[]);
        void send_mav_cmd_nav_takeoff(float _alt, uint16_t &len, uint8_t buf[]);
        void send_mav_cmd_nav_land(uint16_t &len, uint8_t buf[]);
        void send_mav_cmd_nav_rtl(uint16_t &len, uint8_t buf[]);
        void add_mav_cmd_nav_waypoint_int(float _hold_time, float _acc_rad, float _pass_rad, float _yaw, int32_t _lat, int32_t _long, float _alt);
		void upload_mission();
		void download_mission();
		void clear_mission();
		void abort_mission();
        void autopilot_reboot(uint16_t &len, uint8_t buf[]);
		void populate_wp_buf(uint8_t _nWP);
		void show_wp_write_buf();
		void show_wp_read_buf();
        void send_test_ric_msg(uint16_t _id, int16_t _val, uint16_t &len, uint8_t buf[]);

    protected:

    private:
		/* The default UART header for your MCU */
		int sysid = 1;                   ///< ID 20 for this airplane. 1 PX, 255 ground station
		int compid = 158;                ///< The component sending the message
		int type = MAV_TYPE_QUADROTOR;   ///< This system is an airplane / fixed wing

		// Define the system type, in this case an airplane -> on-board controller
		uint8_t system_type = MAV_TYPE_GENERIC;
		uint8_t autopilot_type = MAV_AUTOPILOT_INVALID;

		uint8_t system_mode = MAV_MODE_PREFLIGHT; ///< Booting up
		uint32_t custom_mode = 0;                 ///< Custom mode, can be defined by user/adopter
		uint8_t system_state = MAV_STATE_STANDBY; ///< System ready for flight

		//mission waypoints buffer
		vector<mavlink_mission_item_int_t> miss_buf_wp;
		vector<mavlink_mission_item_int_t> miss_recv_buf_wp;
		bool read_mission_complete = false;
		bool mission_accepted = false;
		bool mission_error = false;


        void send_mav_miss_count_msg(uint8_t _target_system, uint8_t _target_component, MAV_MISSION_TYPE _mission_type, uint16_t _count, uint16_t &len, uint8_t buf[]);
        void send_mav_miss_item_msg(mavlink_mission_item_int_t& _mission_item, uint16_t &len, uint8_t buf[]);
        void send_mav_miss_req_list_msg(uint8_t _target_system, uint8_t _target_component, MAV_MISSION_TYPE _mission_type, uint16_t &len, uint8_t buf[]);
        void send_mav_miss_req_int_msg(uint8_t _target_system, uint8_t _target_component, MAV_MISSION_TYPE _mission_type, uint16_t _seq, uint16_t &len, uint8_t buf[]);
        void send_mav_miss_ack_msg(uint8_t _target_system, uint8_t _target_component, MAV_MISSION_TYPE _mission_type, MAV_MISSION_RESULT _type, uint16_t &len, uint8_t buf[]);
        void send_mav_miss_clear_msg(uint8_t _target_system, uint8_t _target_component, MAV_MISSION_TYPE _mission_type);
		
		mutex& m_cout;

    };

}






#endif //Mavlink_h
