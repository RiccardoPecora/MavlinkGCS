#include "msg_transmit_request.h"
#include "xbee_helper.h"
/*
 * Name: Msg_TransmitRequest
 * Description: Constructor
 */
Msg_TransmitRequest::Msg_TransmitRequest() {}


/*
 * Name: encode
 * Description: encode message in a frame
 */
void Msg_TransmitRequest::encode(uint8_t *buf, uint64_t &len){

    uint64_t idx = 0;
    uint64_t tmp_checksum = 0x0000000000000000;

    //Start delimiter
    buf[idx++] = 0x7E;

    //Length
    buf[idx++] = 0x00;
    buf[idx++] = 0x00;

    //API Identifier
    tmp_checksum += API_ID::TRANSMIT_REQUEST;
    buf[idx++] = API_ID::TRANSMIT_REQUEST;

    //Frame ID
    tmp_checksum += this->frame_id;
    buf[idx++] = this->frame_id;

    //64-bit Destination Address
    uint8_t* ptr_addr = (uint8_t*)&this->dest_addr_64bit;
    for(uint8_t i = sizeof(uint64_t) - 1; i >= 0; i--){
        tmp_checksum += ptr_addr[i];
        buf[idx++] = ptr_addr[i];
        if(i == 0){
            break;
        }
    }

    //16-bit Destination Address
    tmp_checksum += (uint8_t)(this->dest_addr_16bit >> 8);
    buf[idx++] = (uint8_t)(this->dest_addr_16bit >> 8);

    tmp_checksum += (uint8_t)this->dest_addr_16bit;
    buf[idx++] = (uint8_t)this->dest_addr_16bit;

    //Broadcast Radius
    tmp_checksum += this->broadcast_radius;
    buf[idx++] = this->broadcast_radius;

    //Transmit Options
    tmp_checksum += this->transmit_options;
    buf[idx++] = this->transmit_options;

    //Payload Data
    for(uint8_t i = 0; i < this->payload_len; i++){
        if(this->payload_data[i] == 0x7E || this->payload_data[i] == 0x7D ||
            this->payload_data[i] == 0x11 || this->payload_data[i] == 0x13){
            tmp_checksum += 0x7D;
            buf[idx++] = 0x7D;
            uint8_t escaped_byte = this->payload_data[i] ^ 0x20;
            tmp_checksum += escaped_byte;
            buf[idx++] = escaped_byte;
        }else{
            tmp_checksum += this->payload_data[i];
            buf[idx++] = this->payload_data[i];
        }
    }

    //Length
    len = idx - XBEE_FRAME_INIT_OFFSET_BYTE;
    buf[1] = ((uint8_t)(len >> 8)) & 0xFF;
    buf[2] = (uint8_t)len;
    len += XBEE_OTHER_FRAME_BYTES;

    //Checksum
    uint8_t frame_checksum = 0xFF - ((uint8_t)tmp_checksum);
    buf[idx] = frame_checksum;

}


/*
 * Name: decode
 * Description: decode message in a frame
 */
void Msg_TransmitRequest::decode(QByteArray& _msg){

}

