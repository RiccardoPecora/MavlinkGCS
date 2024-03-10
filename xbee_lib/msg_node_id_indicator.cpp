#include "msg_node_id_indicator.h"
#include "xbee_helper.h"

Msg_NodeIdIndicator::Msg_NodeIdIndicator() {}

void Msg_NodeIdIndicator::encode(uint8_t *buf, uint64_t &len){

}

void Msg_NodeIdIndicator::decode(QByteArray& _msg){

    uint8_t idx = 0;
    uint16_t msg_len = _msg.size();
    uint8_t ni_len = msg_len - 34;

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

    //Options
    this->options = _msg[idx++];

    //16-bit Remote Address
    this->remote_addr_16bit = (((uint16_t)_msg[idx]) << 8) | _msg[idx + 1];
    idx++;
    idx++;

    //64-bit Remote Address
    ptr_addr = (uint8_t*)&this->remote_addr_64bit;
    for(uint8_t i = sizeof(uint64_t) - 1; i >= 0; i--){
        ptr_addr[i] = _msg[idx++];
        if(i == 0){
            break;
        }
    }

    //Node Identifier String   
    char *ptr_ni = (char*)&this->node_id_string;
    for(uint8_t i = 0; i < ni_len; i++){
        ptr_ni[i] = _msg[idx++];
    }

    //16-bit Zigbee Parent Address
    this->zigbee_16_bit_parent_address = (((uint16_t)_msg[idx]) << 8) | _msg[idx + 1];
    idx++;
    idx++;

    //Network Device Type
    this->network_device_type = _msg[idx++];

    //Source Event
    this->source_event = _msg[idx++];

    //Digi Profile ID
    this->digi_profile_ID = (((uint16_t)_msg[idx]) << 8) | _msg[idx + 1];
    idx++;
    idx++;

    //Digi Manufacturer ID
    this->digi_manufacturer_ID = (((uint16_t)_msg[idx]) << 8) | _msg[idx + 1];
    idx++;
    idx++;

    // //Device Type Identifier
    // ptr_addr = (uint8_t*)&this->device_type_id;
    // for(uint8_t i = sizeof(uint32_t) - 1; i >= 0; i--){
    //     ptr_addr[i] = _msg[idx++];
    //     if(i == 0){
    //         break;
    //     }
    // }

    // //RSSI
    // this->rssi = _msg[idx++];

    //Checksum
    this->checksum = _msg[idx];

}
