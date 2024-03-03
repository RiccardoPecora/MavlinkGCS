#ifndef XBEE_H
#define XBEE_H

#include <stdint.h>
#include <QObject>

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
    static const uint16_t XBEE_FRAME_INIT_OFFSET_BYTE = 3;

    /*
     * METHODS
     */
    bool parse_xbee_frame(char _byte_read, QByteArray& _msg);


private:
    QByteArray data_buf, msg;
    XBEE::FRAME_STATE frame_state;
    uint xbee_frame_idx = 0;
    uint xbee_frame_len = 0;

};

#endif // XBEE_H
