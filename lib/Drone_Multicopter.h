#ifndef Drone_Multicopter_h
#define Drone_Multicopter_h

#include "Drone_base.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//MACROS
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define DEBUG


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//CLASS
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Drone_Multicopter : public Drone_base{
  public:
    Drone_Multicopter();
    Drone_Multicopter(COMM::Comm_Base* _ptr_comm);

  private:

};


#endif //Drone_Multicopter_h