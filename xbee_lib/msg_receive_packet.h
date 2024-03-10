#ifndef MSG_RECEIVE_PACKET_H
#define MSG_RECEIVE_PACKET_H

#include "msg_base_class.h"

class Msg_ReceivePacket : public Msg_BaseClass
{
public:
    Msg_ReceivePacket();
    void encode(uint8_t *buf, uint64_t &len) override;
    void decode(QByteArray& _msg) override;

public:
    uint64_t src_addr_64bit;
    uint16_t src_addr_16bit;
    uint8_t receive_options = 0x00;
    uint8_t* receive_data = nullptr;
    uint16_t receive_data_len = 0x0000;
};

#endif // MSG_RECEIVE_PACKET_H
