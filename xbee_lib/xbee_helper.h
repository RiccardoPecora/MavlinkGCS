#ifndef XBEE_HELPER_H
#define XBEE_HELPER_H

#include <QObject>
#include "msg_transmit_request.h"
#include "msg_node_id_indicator.h"


#define XBEE_MAX_PACKET_LENGHT 255
#define XBEE_FRAME_INIT_OFFSET_BYTE 3 //start delimiter, length MSB, length LSB,
#define XBEE_OTHER_FRAME_BYTES 4 //start delimiter, length MSB, length LSB, Checksum

// namespace XBEE_NS {
//     class XBEE;
//     class Msg_BaseClass;
//     class Msg_TransmitRequest;
//     class Msg_NodeIdIndicator;
// }

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
    TRANSMIT_REQUEST = 0x10,
    EXPLICIT_ADDRESSING_COMMAND_REQUEST = 0x11,
    REMOTE_AT_COMMAND_REQUEST = 0x17,
    CREATE_SOURCE_ROUTE = 0x21,
    LOCAL_AT_COMMAND_RESPONSE = 0x88,
    MODEM_STATUS = 0x8A,
    EXTENDED_TRANSMIT_STATUS = 0x8B,
    RECEIVE_PACKET = 0x90,
    EXPLICIT_RECEIVE_INDICATOR = 0x91,
    IO_SAMPLE_INDICATOR = 0x92,
    XBEE_SENSOR_READ_INDICATOR = 0x94,
    NODE_IDENTIFICATION_INDICATOR = 0x95,
    REMOTE_AT_COMMAND_RESPONSE= 0x97,
    EXTENDED_MODEM_STATUS = 0x98,
    OVER_THE_AIR_FIRMWARE_UPDATE_STATUS = 0xA0,
    ROUTE_RECORD_INDICATOR = 0xA1,
    MANY_TO_ONE_ROUTE_REQUEST_INDICATOR = 0xA3
};

class Xbee_Helper : public QObject
{
    Q_OBJECT

    /*
     * METHODS
     */
public:
    explicit Xbee_Helper(QObject *parent = nullptr);
    bool parse_xbee_frame(char _byte_read, QByteArray& _msg);

signals:


private:
    /*
     * FIELDS
     */
    QByteArray data_buf, msg;
    FRAME_STATE frame_state;
    uint xbee_frame_idx = 0;
    uint xbee_frame_len = 0;
};

#endif // XBEE_HELPER_H
