
#include "Drone_base.h"

/*
  FUNCTION: Drone (Constructor)
  DESCRIPTION: Constructor
  PARAMETER: none
  RET_VAL: none
*/
Drone_base::Drone_base(){}

/*
  FUNCTION: Drone (Constructor)
  DESCRIPTION: Constructor
  PARAMETER: none
  RET_VAL: none
*/
Drone_base::Drone_base(COMM::Comm_Base* _ptr_comm) {
	this->ptr_comm = _ptr_comm;
}

/*
  FUNCTION: getBatteryVoltage 
  DESCRIPTION: Get battery voltage level
  PARAMETER: none
  RET_VAL: uint8_t
*/
uint8_t Drone_base::getBatteryVoltage() const {
  return battery_voltage;
}

/*
  FUNCTION: setBatteryVoltage
  DESCRIPTION: Set battery voltage level
  PARAMETER: uint8_t _batteryVoltage 
  RET_VAL: uint8_t error_state
*/
uint8_t Drone_base::setBatteryVoltage(uint8_t _batteryVoltage){
	if (_batteryVoltage > MIN_BATTERY_VOLTAGE && _batteryVoltage < MAX_BATTERY_VOLTAGE) {
		this->battery_voltage = _batteryVoltage;
		return 0;
	}
	else {
		return 1;
	}
}

/*
  FUNCTION: setCommModule
  DESCRIPTION: Set Communication module
  PARAMETER: Comm_Base* _comm_mod
  RET_VAL: uint8_t error_state
*/
uint8_t Drone_base::setCommModule(COMM::Comm_Base* _comm_mod) {
	
	if (_comm_mod) {
		this->ptr_comm = _comm_mod;
		return 0;
	}
	else {
		return 1;
	}
}

/*
  FUNCTION: getCommModule
  DESCRIPTION: Get Communication module
  PARAMETER: void
  RET_VAL: Comm_Base*
*/
COMM::Comm_Base* Drone_base::getCommModule() const {
	return ptr_comm;
}


/*
  FUNCTION: getLandingState
  DESCRIPTION: Get Drone landing state
  PARAMETER: none
  RET_VAL: enum_land_state (0 = NOT LANDED, 1 = LANDED)
*/
enum_land_state Drone_base::getLandingState()const{
  return landing_state;
}

/*
  FUNCTION: setLandingState
  DESCRIPTION: Set Drone landing state
  PARAMETER: enum_land_state (0 = NOT LANDED, 1 = LANDED)
  RET_VAL: void
*/
void Drone_base::setLandingState(enum_land_state _land_state){
  this->landing_state = _land_state;
}

/*
  FUNCTION: getArmingState
  DESCRIPTION: Get Drone arming state
  PARAMETER: void
  RET_VAL: enum_arm_state (0 = NOT ARMED, 1 = ARMED)
*/
enum_arm_state Drone_base::getArmingState()const{
  return this->arming_state;
}

/*
  FUNCTION: setArmingState
  DESCRIPTION: Set Drone arming state
  PARAMETER: enum_arm_state _arm_state (0 = NOT ARMED, 1 = ARMED)
  RET_VAL: void
*/
void Drone_base::setArmingState(enum_arm_state _arm_state){
  this->arming_state = _arm_state;
}

/*
  FUNCTION: getChargingState
  DESCRIPTION: Get Drone charging state
  PARAMETER: void
  RET_VAL: enum_charge_state (0 = NOT IN CHARGE, 1 = IN CHARGING, 2= CHARGED)
*/
enum_charge_state Drone_base::getChargingState()const{
  return this->charging_state;
}

/*
  FUNCTION: setChargingState
  DESCRIPTION: Set Drone charging state
  PARAMETER: enum_charge_state _charge_state (0 = NOT IN CHARGE, 1 = IN CHARGING, 2= CHARGED)
  RET_VAL: void
*/
void Drone_base::setChargingState(enum_charge_state _charge_state){
  this->charging_state = _charge_state;
}

