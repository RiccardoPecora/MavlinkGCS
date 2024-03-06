#ifndef XBEE_H
#define XBEE_H

#include <stdint.h>
#include <QObject>

#define XBEE_MAX_PACKET_LENGHT 255
#define XBEE_FRAME_INIT_OFFSET_BYTE 3 //start delimiter, length MSB, length LSB,
#define XBEE_OTHER_FRAME_BYTES 4 //start delimiter, length MSB, length LSB, Checksum

class XBEE : public QObject
{
    Q_OBJECT

public:
    /*
     * FIELDS
     */

    XBEE();
    enum FRAME_STATE{
        START_DELIMITER = 0,
        LENGTH,
        FRAME_TYPE,
        DATA,
        CHECK_SUM
    };

    enum API_ID{
        LOCAL_AT_COMMAND_REQUEST = 0x08,
        QUEUE_AT_COMMAND_REQUEST = 0x09,
        TRANSMIT_REQUEST = 0x10
        // Explicit Addressing Command Request = 0x11,
        // Remote AT Command Request = 0x17,
        // Create Source Route = 0x21,
        // Local AT Command Response = 0x88,
        // Modem Status = 0x8A,
        // Extended Transmit Status = 0x8B,
        // Receive Packet = 0x90,
        // Explicit Receive Indicator = 0x91,
        // I/O Sample Indicator = 0x92,
        // XBee Sensor Read Indicator = 0x94,
        // Node Identification Indicator = 0x95,
        // Remote AT Command Response= 0x97,
        // Extended Modem Status = 0x98,
        // Over=the=Air Firmware Update Status = 0xA0,
        // Route Record Indicator = 0xA1,
        // Many=to=One Route Request Indicator = 0xA3
    };

    class Frame
    {
    public:
        Frame() : frame_type(API_ID::TRANSMIT_REQUEST){}
        uint8_t frame_type;
        uint64_t dest_addr_64bit;
        uint16_t dest_addr_16bit;
    };

    class Tx_Req_Frame : public Frame
    {
    public:
        Tx_Req_Frame() : Frame(){}
        uint8_t frame_id = 0x00;
        uint8_t broadcast_radius = 0x00;
        uint8_t transmit_options = 0x00;
        uint8_t* payload_data = nullptr;
        uint64_t payload_len = 0x0000000000000000;
    };

    /*
     * METHODS
     */
    bool parse_xbee_frame(char _byte_read, QByteArray& _msg);
    void frame_pack(Frame &_frame, uint8_t *_xbee_buf, uint64_t &_frame_len);

private:
    QByteArray data_buf, msg;
    XBEE::FRAME_STATE frame_state;
    uint xbee_frame_idx = 0;
    uint xbee_frame_len = 0;

};

#endif // XBEE_H
