#include "xbee.h"

XBEE::XBEE() {
    data_buf.clear();
    msg.clear();
    frame_state = XBEE::START_DELIMITER;
    xbee_frame_idx = 0;
    xbee_frame_len = 0;
}

/*
 * parse_xbee_frame
 *
 */
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
                xbee_frame_len += XBEE_FRAME_INIT_OFFSET_BYTE;
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


/*
 * frame_pack
 *
 */
void XBEE::frame_pack(uint8_t* _msg, uint64_t _msg_len, uint8_t *_xbee_buf, uint64_t &_frame_len){
    uint64_t idx = 0;
    uint64_t tmp_checksum = 0x0000000000000000;

    //Start delimiter
    _xbee_buf[idx++] = 0x7E;

    //Length
    _xbee_buf[idx++] = 0x00;
    _xbee_buf[idx++] = 0x00;

    //API Identifier
    tmp_checksum += 0x10;
    _xbee_buf[idx++] = 0x10; //Transmit Request

    //Data
    for(uint8_t i = 0; i < _msg_len; i++){
        if(_msg[i] == 0x7E || _msg[i] == 0x7D ||_msg[i] == 0x11 ||_msg[i] == 0x13){
            tmp_checksum += _msg[i];
            _xbee_buf[idx++] = 0x7D;
            uint8_t escaped_byte = _msg[i] ^ 0x20;
            tmp_checksum += escaped_byte;
            _xbee_buf[idx++] = escaped_byte;
        }else{
            tmp_checksum += _msg[i];
           _xbee_buf[idx++] = _msg[i];
        }
    }

    //Length
    _frame_len = idx - 3;
    _xbee_buf[1] = ((uint8_t)(_frame_len >> 8)) & 0xFF;
    _xbee_buf[2] = (uint8_t)_frame_len;
    _frame_len += XBEE_OTHER_FRAME_BYTES;

    //Checksum
    uint8_t frame_checksum = 0xFF - ((uint8_t)tmp_checksum);
    _xbee_buf[idx] = frame_checksum;
}
