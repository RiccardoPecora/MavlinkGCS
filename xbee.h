#ifndef XBEE_H
#define XBEE_H

#include <stdint.h>

class XBEE
{
public:
    XBEE();
    enum FRAME_STATE{
        START_DELIMITER = 0,
        LENGTH,
        FRAME_TYPE,
        DATA,
        CHECK_SUM
    };
    static const uint16_t XBEE_FRAME_INIT_OFFSET_BYTE = 3;
};

#endif // XBEE_H
