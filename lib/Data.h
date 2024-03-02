
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//MACROS
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define DEBUG
#define UAVS_LIST_LENGTH 2
#define NODE_DISCOVERY_INTERVALL 20000
#define BATTERY_STATE_INTERVALL 8000
#define XBEE_PACKET_TIMEOUT 2000
#define CHARGE_STATION_NUM 2
#define MSG_CODE_LENGTH 2 //bytes
#define MSG_CODE_BAT_STS_REQ 0x0001
#define MSG_CODE_BAT_STS_RESP 0x0002
#define MSG_CODE_GO_TO_PARK_REQ 0x0003

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//STRUCTS
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//VARIABLES
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const uint8_t CMD_BAT_STS_REQ[] = {0x00, 0x01};
const uint8_t CMD_BAT_STS_RESP[] = {0x00, 0x02};
const uint8_t CMD_GO_TO_PARK_REQ[] = {0x00, 0x03};

const uint8_t AT_CMD_ND[] = "ND";// Node Discover
const uint8_t AT_CMD_SH[] = "SH";// serial high
const uint8_t AT_CMD_SL[] = "SL";// serial low
const uint8_t AT_CMD_AI[] = "AI";// association status





