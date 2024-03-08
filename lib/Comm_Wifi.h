#ifndef Comm_Wifi_h
#define Comm_Wifi_h

#include "Comm_Base.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//MACROS
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define DEBUG

namespace COMM {

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//CLASS
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	class Comm_Wifi : public Comm_Base {
	public:
		Comm_Wifi();
        uint8_t send(uint8_t* _ptr_send_buf, uint8_t _buf_len);

	private:

	};

}
#endif //Comm_Wifi_h

