#ifndef Drone_base_h
#define Drone_base_h

#include <iostream> 
#include <inttypes.h>
#include "Comm_base.h"

using namespace std;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//MACROS
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define DEBUG
#define MAX_BATTERY_VOLTAGE 80
#define MIN_BATTERY_VOLTAGE 0

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//STRUCTS
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//CLASS
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Drone_base{
  public:
    Drone_base();
    Drone_base(COMM::Comm_Base* _ptr_comm);
    uint8_t getBatteryVoltage() const;
    uint8_t setBatteryVoltage(uint8_t _batteryVoltage);
    uint8_t setCommModule(COMM::Comm_Base* _comm_mod);
    COMM::Comm_Base* getCommModule() const;
	
    enum_land_state getLandingState()const;
    void setLandingState(enum_land_state _land_state);
    enum_arm_state getArmingState()const;
    void setArmingState(enum_arm_state _arm_state);
    enum_charge_state getChargingState()const;
    void setChargingState(enum_charge_state _charge_state);

  protected:
    COMM::Comm_Base* ptr_comm = nullptr;
    uint8_t battery_voltage = 0;
    enum_land_state landing_state = enum_land_state::NOT_LANDED;
    enum_arm_state arming_state = enum_arm_state::DRONE_NOT_ARMED;
    enum_charge_state charging_state = enum_charge_state::NOT_IN_CHARGE;
};

#endif //Drone_base_h