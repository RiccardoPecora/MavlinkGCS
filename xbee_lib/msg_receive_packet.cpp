#include "msg_receive_packet.h"
#include "qdebug.h"

Msg_ReceivePacket::Msg_ReceivePacket() {}

void Msg_ReceivePacket::encode(uint8_t *buf, uint64_t &len)
{

}

void Msg_ReceivePacket::decode(QByteArray &_msg)
{
    uint8_t idx = 0;
    uint16_t msg_len = _msg.size();

    //Start Delimiter
    this->start_delimiter = _msg[idx++];

    //Length
    this->length = (((uint16_t)_msg[idx]) << 8) | _msg[idx + 1];
    idx++;
    idx++;

    //Frame Type
    this->frame_type = _msg[idx++];

    //64-bit Source Address
    uint8_t* ptr_addr = (uint8_t*)&this->src_addr_64bit;
    for(uint8_t i = sizeof(uint64_t) - 1; i >= 0; i--){
        ptr_addr[i] = _msg[idx++];
        if(i == 0){
            break;
        }
    }

    //16-bit Source Address
    this->src_addr_16bit = (((uint16_t)_msg[idx]) << 8) | _msg[idx + 1];
    idx++;
    idx++;

    //Receive Options
    this->receive_options = _msg[idx++];

    //Receive Data Length
    this->receive_data_len = msg_len - 16;

    //Receive Data
    this->receive_data = new uint8_t[this->receive_data_len];
    uint8_t *ptr_rcv_data = this->receive_data;
    for(uint16_t i = 0 ; i < this->receive_data_len; i++){
        ptr_rcv_data[i] = _msg[idx++];
    }

    //Checksum
    this->checksum = _msg[idx];
}
