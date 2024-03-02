#include "Charger_Base.h"

/*
  FUNCTION: Charger_Base (Constructor)
  DESCRIPTION: Constructor
  PARAMETER: none
  RET_VAL: none
*/
Charger_Base::Charger_Base(){

}

/*
  FUNCTION: centrage_start
  DESCRIPTION: Centrage start procedure
  PARAMETER: none
  RET_VAL: enum_centrage_state
*/
enum_centrage_state Charger_Base::centrage_start(){
	return enum_centrage_state::CENTERED;
}

/*
  FUNCTION: centrage_stop
  DESCRIPTION: Centrage stop procedure 
  PARAMETER: none
  RET_VAL: enum_centrage_state
*/
enum_centrage_state Charger_Base::centrage_stop(){
	return enum_centrage_state::NOT_CENTERED;
}

/*
  FUNCTION: centrage_reset
  DESCRIPTION: Centrage reset proedure 
  PARAMETER: none
  RET_VAL: enum_centrage_state
*/
enum_centrage_state Charger_Base::centrage_reset(){
	return enum_centrage_state::NOT_CENTERED;
}

/*
  FUNCTION: get_centrage_state
  DESCRIPTION: Get centrage state  
  PARAMETER: none
  RET_VAL: enum_centrage_state
*/
enum_centrage_state Charger_Base::get_centrage_state(){
	return enum_centrage_state::NOT_CENTERED;
}

/*
  FUNCTION: power_switch_arm
  DESCRIPTION: Power switch arm procedure
  PARAMETER: none
  RET_VAL: enum_pow_sw_state
*/
enum_pow_sw_state Charger_Base::power_switch_arm(){
	return enum_pow_sw_state::POW_SW_ARMED;
}

/*
  FUNCTION: power_switch_disarm
  DESCRIPTION: Power switch disarm procedure
  PARAMETER: none
  RET_VAL: enum_pow_sw_state
*/
enum_pow_sw_state Charger_Base::power_switch_disarm(){
	return enum_pow_sw_state::POW_SW_DISARMED;
}

/*
  FUNCTION: get_power_switch_state
  DESCRIPTION: Get power switch state
  PARAMETER: none
  RET_VAL: enum_pow_sw_state
*/
enum_pow_sw_state Charger_Base::get_power_switch_state(){
	return enum_pow_sw_state::POW_SW_DISARMED;
}

/*
  FUNCTION: get_charge_station_state
  DESCRIPTION: Get charge station state
  PARAMETER: void
  RET_VAL: charge_station_struct*
*/
charge_station_struct* Charger_Base::get_charge_station_state(){
	return &charge_station;
}










