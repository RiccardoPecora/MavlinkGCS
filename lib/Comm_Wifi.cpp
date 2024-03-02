#include "Comm_Wifi.h"

COMM::Comm_Wifi::Comm_Wifi() : Comm_Base() {
	
}


uint8_t COMM::Comm_Wifi::send(uint8_t* _ptr_send_buf, uint8_t _buf_len) {
	printf("Send method from Comm_Wifi class\n");
	return 0;
}