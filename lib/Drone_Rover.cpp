#include "Drone_Rover.h"

/*
  FUNCTION: Drone_Rover (Constructor)
  DESCRIPTION: Constructor
  PARAMETER: none
  RET_VAL: none
*/
Drone_Rover::Drone_Rover() : Drone_base() {

}

/*
  FUNCTION: Drone_Rover (Constructor)
  DESCRIPTION: Constructor
  PARAMETER: Comm_Base* _ptr_comm
  RET_VAL: none
*/
Drone_Rover::Drone_Rover(COMM::Comm_Base* _ptr_comm) : Drone_base(_ptr_comm) {

}


