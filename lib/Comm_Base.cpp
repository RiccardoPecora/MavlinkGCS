#include "Comm_Base.h"

COMM::Comm_Base::Comm_Base() {
	
}

int8_t COMM::Comm_Base::init() {
	return 0;
}

int8_t COMM::Comm_Base::begin() {
	return 0;
}

int8_t COMM::Comm_Base::connect() {
    return 0;
}

int8_t COMM::Comm_Base::close() {
    return 0;
}

int8_t COMM::Comm_Base::encode(const uint8_t* _cmd, uint32_t* _param, uint8_t& _param_num, uint8_t* _param_dim, uint8_t*& _ptr_payload, uint8_t& _payload_length) {
    
    printf("Comm_Base - Encode method - Start \n");
    static uint8_t payload_len = 3;
    for (uint8_t i = 0; i < _param_num; i++) {
        payload_len += (_param_dim[i] + 1);
    }

    static uint8_t payload[50];
    //printf("Comm_Base - Encode method - &Payload: %p \n", payload);

    payload[0] = (uint8_t)'$';
    payload[1] = _cmd[0];
    payload[2] = _cmd[1];

    uint8_t idx = 0;

    for (uint8_t i = 0; i < _param_num; i++) {
        uint32_t par = _param[i];
        for (uint8_t j = 0; j < _param_dim[i]; j++) {
            payload[3+idx] = (uint8_t)((par >> j * 8) & 0x0000000000FF);
            idx++;
        }
        payload[3 + idx] = '@';
        idx++;
    }

    _ptr_payload = payload;
    _payload_length = payload_len;

    for (uint8_t i = 0; i < _payload_length; i++) {
        printf("Comm_Base - Encode method - Payload[%d]: %x \n", i,_ptr_payload[i]);
    }
    

    printf("Comm_Base - Encode method - End \n");

    return 0;
}

int8_t COMM::Comm_Base::decode(uint8_t*& _ptr_payload, uint8_t& _payload_length) {
    printf("Comm_Base - Decode method - Start \n");

    /*
    for (uint8_t i = 0; i < _payload_length; i++) {
        printf("Comm_Base - Decode method - Payload[%d]: %x \n", i, _ptr_payload[i]);
    }
    */

    uint8_t cmd[2] = {0, 0};
    uint8_t param_num = 0;
    uint32_t param[4]{ 0, 0, 0, 0};

    uint8_t idx = 0;
    uint8_t cmd_idx = 0;
    uint32_t app = 0;
    int8_t frame_start = -1;
    for (uint8_t i = 0; i < _payload_length; i++) {  
        if (_ptr_payload[i] == '$') {
            frame_start = i;
            continue;
        }

        if (frame_start > -1) {
            if (i <= frame_start + 2) {
                cmd[cmd_idx] = _ptr_payload[i];
                cmd_idx++;
            }
            else if (_ptr_payload[i] == '@') {
                param[param_num] = app;
                param_num++;
                app = 0;
                //continue;
            }
            else {
                app = app | ((uint32_t)_ptr_payload[i]) << (idx * 8);
                idx++;
            }
        }
        else {
            continue;
        }   
    }

    for (uint8_t i = 0; i < param_num; i++) {
        printf("Comm_Base - Decode method - Param[%d]: %d \n", i, param[i]);
    }

    printf("Comm_Base - Decode method - End \n");
    return 0;
}

int8_t COMM::Comm_Base::send(uint8_t*& _ptr_buf, uint16_t& _buf_len) {
	printf("Send method from Comm_Base class \n");
	return 0;
}

int8_t COMM::Comm_Base::receive(uint8_t*& _ptr_buf, uint16_t& _buf_len) {
    printf("Receive method from Comm_Base class \n");
    return 0;

}

