#ifndef Charger_Base_h
#define Charger_Base_h

#include <inttypes.h>

using namespace std;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//MACROS
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define DEBUG


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//STRUCTS
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
enum enum_centrage_state{
  NOT_CENTERED = 0,
  CENTERING_IN_PROGRESS = 1,
  CENTERED = 2
};

enum enum_pow_sw_state{
  POW_SW_DISARMED = 0,
  POW_SW_ARMED = 1
};

enum enum_station_state{
  FREE = 0,
  BUSY = 1
};

struct charge_station_struct{
  enum_station_state state = enum_station_state::FREE;
  enum_centrage_state centrage_state = enum_centrage_state::NOT_CENTERED;
  enum_pow_sw_state pw_sw_state = enum_pow_sw_state::POW_SW_DISARMED;
};


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//CLASS
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Charger_Base{
  public:
    Charger_Base();
    virtual enum_centrage_state centrage_start();
    virtual enum_centrage_state centrage_stop();
    virtual enum_centrage_state centrage_reset();
    virtual enum_centrage_state get_centrage_state();
    virtual enum_pow_sw_state power_switch_arm();
    virtual enum_pow_sw_state power_switch_disarm();
    virtual enum_pow_sw_state get_power_switch_state();
    virtual charge_station_struct* get_charge_station_state();

  private:
    charge_station_struct charge_station;


};


#endif //Charger_Base_h