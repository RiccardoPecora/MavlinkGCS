#ifndef MSG_NODE_ID_INDICATOR_H
#define MSG_NODE_ID_INDICATOR_H

#include "msg_base_class.h"

class Msg_NodeIdIndicator : public Msg_BaseClass
{
public:
    Msg_NodeIdIndicator();
    void encode(uint8_t *buf, uint64_t &len) override;
    void decode(QByteArray& _msg) override;

public:
    uint64_t src_addr_64bit;
    uint16_t src_addr_16bit;
    uint8_t options = 0x00;
    uint16_t remote_addr_16bit = 0x0000;
    uint64_t remote_addr_64bit = 0x0000000000000000;
    char node_id_string[20] {0};
    uint16_t zigbee_16_bit_parent_address = 0x0000;
    uint8_t network_device_type = 0x00;
    uint8_t source_event = 0x00;
    uint16_t digi_profile_ID = 0x0000;
    uint16_t digi_manufacturer_ID = 0x0000;
    uint32_t device_type_id = 0x00000000;
    uint8_t rssi = 0x00;
};

#endif // MSG_NODE_ID_INDICATOR_H
