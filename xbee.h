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

    /*
     * METHODS
     */
    bool parse_xbee_frame(char _byte_read, QByteArray& _msg);
    void frame_pack(uint8_t* _msg, uint64_t _msg_len, uint8_t *_xbee_buf, uint64_t &_frame_len);

private:
    QByteArray data_buf, msg;
    XBEE::FRAME_STATE frame_state;
    uint xbee_frame_idx = 0;
    uint xbee_frame_len = 0;

};

#endif // XBEE_H
