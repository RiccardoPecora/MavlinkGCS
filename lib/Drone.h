#ifndef Drone_h
#define Drone_h
#include <XBee.h>


//#define DEBUG

struct xbee_node_data_struct{
  uint16_t xbee_addr16 = 0;
  XBeeAddress64 xbee_addr64 = 0;
  // uint32_t sh = 0;
  // uint32_t sl = 0;
  char ni[20];
  uint16_t pna = 0;
  uint8_t dev_type = 0;
  // uint8_t status = 0;
  uint16_t profile_id = 0;
  uint16_t manuf_id = 0;
};

enum enum_land_state{
  NOT_LANDED = 0,
  LANDED = 1,
};

enum enum_arm_state{
  DRONE_NOT_ARMED = 0,
  DRONE_ARMED = 1,
};

enum enum_charge_state{
  NOT_IN_CHARGE = 0,
  IN_CHARGING = 1,
  CHARGED = 2,
};

class Drone{
  public:
    Drone();
    Drone(XBeeAddress64 _xbee_addr64, uint16_t _xbee_addr16, char* _ni, uint16_t _pna, uint8_t _dev_type, uint16_t _profile_id, uint16_t _manuf_id);
    uint8_t getBatteryVoltage();
    void setBatteryVoltage(uint8_t _batteryVoltage);
	void setXbeeAddr64(XBeeAddress64 _xbee_addr64);
    XBeeAddress64 getXbeeAddr64()const;
    uint16_t getXbeeAddr16()const;
    const char* getXbeeNI()const;
    uint16_t getXbeePNA()const;
    uint8_t getXbeeDevType()const;
    uint16_t getXbeeProfileID()const;
    uint16_t getXbeeManufID()const;
    enum_land_state getLandingState()const;
    void setLandingState(enum_land_state _land_state);
    enum_arm_state getArmingState()const;
    void setArmingState(enum_arm_state _arm_state);
    enum_charge_state getChargingState()const;
     void setChargingState(enum_charge_state _charge_state);

  private:
    struct xbee_node_data_struct xbee_node_data;
    uint8_t battery_voltage = 0;
    enum_land_state landing_state = enum_land_state::NOT_LANDED;
    enum_arm_state arming_state = enum_arm_state::DRONE_NOT_ARMED;
    enum_charge_state charging_state = enum_charge_state::NOT_IN_CHARGE;
};


#endif //Drone_h