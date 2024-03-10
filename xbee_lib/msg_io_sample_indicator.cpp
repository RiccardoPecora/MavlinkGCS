#include "msg_io_sample_indicator.h"

Msg_IOSampleIndicator::Msg_IOSampleIndicator() {}

/*
 * Name: encode
 * Description: encode message in a frame
 */
void Msg_IOSampleIndicator::encode(uint8_t *buf, uint64_t &len)
{

}

/*
 * Name: decode
 * Description: decode message in a frame
 */
void Msg_IOSampleIndicator::decode(QByteArray &_msg)
{
    uint8_t idx = 0;
   // uint16_t msg_len = _msg.size();

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

    //Number of Samples
    this->number_of_samples = _msg[idx++];

    //Digital Sample Mask
    this->digital_sample_mask = (((uint16_t)_msg[idx]) << 8) | _msg[idx + 1];
    idx++;
    idx++;

    //Analog Sample Mask
    this->analog_sample_mask = _msg[idx++];

    //Digital Sample
    if(this->digital_sample_mask){
        this->digital_samples = (((uint16_t)_msg[idx]) << 8) | _msg[idx + 1];
        idx++;
        idx++;
    }

    //Analog Sample
    if(this->analog_sample_mask){
        this->analog_samples = (((uint16_t)_msg[idx]) << 8) | _msg[idx + 1];
        idx++;
        idx++;
    }
    //Checksum
    this->checksum = _msg[idx];
}
