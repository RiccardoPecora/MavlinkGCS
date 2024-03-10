#ifndef MSG_TRANSMIT_REQUEST_H
#define MSG_TRANSMIT_REQUEST_H

#include "msg_base_class.h"

class Msg_TransmitRequest : public Msg_BaseClass
{
public:
    Msg_TransmitRequest();
    void encode(uint8_t *buf, uint64_t &len) override;
    void decode(QByteArray& _msg) override;

public:
    uint8_t frame_id = 0x00;
    uint64_t dest_addr_64bit;
    uint16_t dest_addr_16bit;
    uint8_t broadcast_radius = 0x00;
    uint8_t transmit_options = 0x00;
    uint8_t* payload_data = nullptr;
    uint64_t payload_len = 0x0000000000000000;
};

#endif // MSG_TRANSMIT_REQUEST_H
