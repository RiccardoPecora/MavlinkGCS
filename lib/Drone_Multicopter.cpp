
#include "Drone_Multicopter.h"

/*
  FUNCTION: Drone_Multicopter (Constructor)
  DESCRIPTION: Constructor
  PARAMETER: none
  RET_VAL: none
*/
Drone_Multicopter::Drone_Multicopter() : Drone_base() {

}

/*
  FUNCTION: Drone_Multicopter (Constructor)
  DESCRIPTION: Constructor
  PARAMETER: Comm_Base* _ptr_comm
  RET_VAL: none
*/
Drone_Multicopter::Drone_Multicopter(COMM::Comm_Base* _ptr_comm) : Drone_base(_ptr_comm) {

}

