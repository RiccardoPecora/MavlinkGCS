#include "xbee_helper.h"

Xbee_Helper::Xbee_Helper(QObject *parent)
    : QObject{parent}
{
    data_buf.clear();
    msg.clear();
    frame_state = START_DELIMITER;
    xbee_frame_idx = 0;
    xbee_frame_len = 0;
}

/*
 * parse_xbee_frame
 *
 */
bool Xbee_Helper::parse_xbee_frame(char _byte_read, QByteArray& _msg){
    bool success = false;
    switch(frame_state){
    case START_DELIMITER:{
        if(_byte_read == 0x7E){
            data_buf.clear();
            msg.clear();
            data_buf.append(_byte_read);
            xbee_frame_idx = 1;
            frame_state = LENGTH;
        }
        break;
    }

    case LENGTH:{
        if(xbee_frame_idx == 1){
            data_buf.append(_byte_read);
            xbee_frame_len += _byte_read << 8;
            xbee_frame_idx++;
        }else if(xbee_frame_idx == 2){
            data_buf.append(_byte_read);
            xbee_frame_len += _byte_read;
            xbee_frame_len += XBEE_FRAME_INIT_OFFSET_BYTE;
            xbee_frame_idx++;
            frame_state = FRAME_TYPE;
        }
        break;
    }

    case FRAME_TYPE:{
        if(xbee_frame_idx < xbee_frame_len - 1){
            data_buf.append(_byte_read);
            xbee_frame_idx++;
            frame_state = DATA;
        }
        break;
    }

    case DATA:{
        if(xbee_frame_idx < xbee_frame_len - 1){
            data_buf.append(_byte_read);
            xbee_frame_idx++;
        }else if(xbee_frame_idx == xbee_frame_len - 1){
            data_buf.append(_byte_read);
            xbee_frame_idx++;
            frame_state = CHECK_SUM;
        }
        break;
    }

    case CHECK_SUM:{
        if(xbee_frame_idx == xbee_frame_len){
            data_buf.append(_byte_read);
            _msg = data_buf;
            xbee_frame_idx = 0;
            xbee_frame_len = 0;
            data_buf.clear();
            frame_state = START_DELIMITER;
            success = true;
        }
        break;
    }
    }
    return success;
}
