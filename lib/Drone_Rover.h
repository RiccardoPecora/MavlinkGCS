#ifndef Drone_Rover_h
#define Drone_Rover_h

#include "Drone_base.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//MACROS
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define DEBUG


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//CLASS
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Drone_Rover : public Drone_base {
public:
    Drone_Rover();
    Drone_Rover(COMM::Comm_Base* _ptr_comm);


private:

};


#endif //Drone_Rover_h

