#include "xbee.h"

XBEE::XBEE() {
    data_buf.clear();
    msg.clear();
    frame_state = XBEE::START_DELIMITER;
    xbee_frame_idx = 0;
    xbee_frame_len = 0;
}


bool XBEE::parse_xbee_frame(char _byte_read, QByteArray& _msg){
    bool success = false;
    switch(frame_state){
        case XBEE::START_DELIMITER:{
            if(_byte_read == 0x7E){
                data_buf.clear();
                msg.clear();
                data_buf.append(_byte_read);
                xbee_frame_idx = 1;
                frame_state = XBEE::LENGTH;
            }
            break;
        }

        case XBEE::LENGTH:{
            if(xbee_frame_idx == 1){
                data_buf.append(_byte_read);
                xbee_frame_len += _byte_read << 8;
                xbee_frame_idx++;
            }else if(xbee_frame_idx == 2){
                data_buf.append(_byte_read);
                xbee_frame_len += _byte_read;
                xbee_frame_len += XBEE::XBEE_FRAME_INIT_OFFSET_BYTE;
                xbee_frame_idx++;
                frame_state = XBEE::FRAME_TYPE;
            }
            break;
        }

        case XBEE::FRAME_TYPE:{
            if(xbee_frame_idx < xbee_frame_len - 1){
                data_buf.append(_byte_read);
                xbee_frame_idx++;
                frame_state = XBEE::DATA;
            }
            break;
        }

        case XBEE::DATA:{
            if(xbee_frame_idx < xbee_frame_len - 1){
                data_buf.append(_byte_read);
                xbee_frame_idx++;
            }else if(xbee_frame_idx == xbee_frame_len - 1){
                data_buf.append(_byte_read);
                xbee_frame_idx++;
                frame_state = XBEE::CHECK_SUM;
            }
            break;
        }

        case XBEE::CHECK_SUM:{
            if(xbee_frame_idx == xbee_frame_len){
                data_buf.append(_byte_read);
                _msg = data_buf;
                xbee_frame_idx = 0;
                xbee_frame_len = 0;
                data_buf.clear();
                frame_state = XBEE::START_DELIMITER;
                success = true;
            }
            break;
        }
    }
    return success;
}
