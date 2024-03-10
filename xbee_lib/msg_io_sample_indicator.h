#ifndef MSG_IOSAMPLEINDICATOR_H
#define MSG_IOSAMPLEINDICATOR_H

#include "msg_base_class.h"

class Msg_IOSampleIndicator : public Msg_BaseClass
{
public:
    Msg_IOSampleIndicator();
    void encode(uint8_t *buf, uint64_t &len) override;
    void decode(QByteArray& _msg) override;

public:
    uint64_t src_addr_64bit = 0x0000000000000000;
    uint16_t src_addr_16bit = 0x0000;
    uint8_t receive_options = 0x00;
    uint8_t number_of_samples = 0x00;
    uint16_t digital_sample_mask = 0x0000;
    uint8_t analog_sample_mask = 0x00;
    uint16_t digital_samples = 0x0000;
    uint16_t analog_samples = 0x0000;

};

#endif // MSG_IOSAMPLEINDICATOR_H
