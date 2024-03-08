#include "XBee.h"
#include "Drone.h"

/*
  FUNCTION: Drone (Constructor)
  DESCRIPTION: Constructor
  PARAMETER: none
  RET_VAL: none
*/
Drone::Drone(){}

/*
  FUNCTION: Drone (Constructor)
  DESCRIPTION: Constructor
  PARAMETER: uint32_t _addrMsb 
             uint32_t _addrLsb
  RET_VAL: none
*/
Drone::Drone(XBeeAddress64 _xbee_addr64, uint16_t _xbee_addr16, char* _ni, uint16_t _pna, uint8_t _dev_type, uint16_t _profile_id, uint16_t _manuf_id){
        xbee_node_data.xbee_addr64 = _xbee_addr64; 
        xbee_node_data.xbee_addr16 = _xbee_addr16; 
        xbee_node_data.pna = _pna; 
        xbee_node_data.dev_type = _dev_type; 
        xbee_node_data.profile_id = _profile_id; 
        xbee_node_data.manuf_id = _manuf_id;
        for(uint8_t i = 0; i < 20; i++){
          xbee_node_data.ni[i] = _ni[i];
        }
       }

/*
  FUNCTION: getBatteryVoltage 
  DESCRIPTION: Get battery voltage level
  PARAMETER: none
  RET_VAL: uint8_t
*/
uint8_t Drone::getBatteryVoltage(){
  return battery_voltage;
}

/*
  FUNCTION: setBatteryVoltage
  DESCRIPTION: Set battery voltage level
  PARAMETER: uint8_t _batteryVoltage 
  RET_VAL: none
*/
void Drone::setBatteryVoltage(uint8_t _batteryVoltage){
  battery_voltage = _batteryVoltage;
}


/*
  FUNCTION: setXbeeAddr64
  DESCRIPTION: Set Xbee module address (64 bit) of the drone
  PARAMETER: XBeeAddress64 _xbee_addr64
  RET_VAL: none
*/
void Drone::setXbeeAddr64(XBeeAddress64 _xbee_addr64){
	xbee_node_data.xbee_addr64 = _xbee_addr64;
}

/*
  FUNCTION: getXbeeAddr64
  DESCRIPTION: Get Xbee module address (64 bit) of the drone
  PARAMETER: none
  RET_VAL: XBeeAddress64
*/
XBeeAddress64 Drone::getXbeeAddr64() const{
  return xbee_node_data.xbee_addr64;
}

/*
  FUNCTION: getXbeeAddr16
  DESCRIPTION: Get Xbee module address (16 bit) of the drone
  PARAMETER: none
  RET_VAL: uint16_t
*/
uint16_t Drone::getXbeeAddr16() const{
  return xbee_node_data.xbee_addr16;
}

/*
  FUNCTION: getXbeeNI
  DESCRIPTION: Get Xbee module address (16 bit) of the drone
  PARAMETER: none
  RET_VAL: char*
*/
const char* Drone::getXbeeNI() const{
  return xbee_node_data.ni;
}

/*
  FUNCTION: getXbeePNA
  DESCRIPTION: Get Xbee module Parent Area Network
  PARAMETER: none
  RET_VAL: uint16_t
*/
uint16_t Drone::getXbeePNA() const{
  return xbee_node_data.pna;
}

/*
  FUNCTION: getXbeeDevType
  DESCRIPTION: Get Xbee module Device Type
  PARAMETER: none
  RET_VAL: uint8_t
*/
uint8_t Drone::getXbeeDevType() const{
  return xbee_node_data.dev_type;
}

/*
  FUNCTION: getXbeeProfileID
  DESCRIPTION: Get Xbee module Profile ID
  PARAMETER: none
  RET_VAL: uint16_t
*/
uint16_t Drone::getXbeeProfileID() const{
  return xbee_node_data.profile_id;
}

/*
  FUNCTION: getXbeeManufID
  DESCRIPTION: Get Xbee module Manufacturer ID
  PARAMETER: none
  RET_VAL: uint16_t
*/
uint16_t Drone::getXbeeManufID() const{
  return xbee_node_data.manuf_id;
}

/*
  FUNCTION: getLandingState
  DESCRIPTION: Get Drone landing state
  PARAMETER: none
  RET_VAL: enum_land_state (0 = NOT LANDED, 1 = LANDED)
*/
enum_land_state Drone::getLandingState()const{
  return landing_state;
}

/*
  FUNCTION: setLandingState
  DESCRIPTION: Set Drone landing state
  PARAMETER: enum_land_state (0 = NOT LANDED, 1 = LANDED)
  RET_VAL: void
*/
void Drone::setLandingState(enum_land_state _land_state){
  this->landing_state = _land_state;
}

/*
  FUNCTION: getArmingState
  DESCRIPTION: Get Drone arming state
  PARAMETER: void
  RET_VAL: enum_arm_state (0 = NOT ARMED, 1 = ARMED)
*/
enum_arm_state Drone::getArmingState()const{
  return this->arming_state;
}

/*
  FUNCTION: setArmingState
  DESCRIPTION: Set Drone arming state
  PARAMETER: enum_arm_state _arm_state (0 = NOT ARMED, 1 = ARMED)
  RET_VAL: void
*/
void Drone::setArmingState(enum_arm_state _arm_state){
  this->arming_state = _arm_state;
}

/*
  FUNCTION: getChargingState
  DESCRIPTION: Get Drone charging state
  PARAMETER: void
  RET_VAL: enum_charge_state (0 = NOT IN CHARGE, 1 = IN CHARGING, 2= CHARGED)
*/
enum_charge_state Drone::getChargingState()const{
  return this->charging_state;
}

/*
  FUNCTION: setChargingState
  DESCRIPTION: Set Drone charging state
  PARAMETER: enum_charge_state _charge_state (0 = NOT IN CHARGE, 1 = IN CHARGING, 2= CHARGED)
  RET_VAL: void
*/
void Drone::setChargingState(enum_charge_state _charge_state){
  this->charging_state = _charge_state;
}

