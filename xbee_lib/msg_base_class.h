#ifndef MSG_BASE_CLASS_H
#define MSG_BASE_CLASS_H

#include <stdint.h>
#include <QObject>

class Msg_BaseClass
{
public:
    Msg_BaseClass();
    virtual void encode(uint8_t *buf, uint64_t &len) = 0;
    virtual void decode(QByteArray& _msg) = 0;

protected:
    uint8_t start_delimiter;
    uint16_t length;
    uint8_t frame_type;
    uint8_t checksum;
};

#endif // MSG_BASE_CLASS_H
