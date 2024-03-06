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
void XBEE::frame_pack(Frame &_frame, uint8_t *_xbee_buf, uint64_t &_frame_len){
    uint64_t idx = 0;
    uint64_t tmp_checksum = 0x0000000000000000;

    //Start delimiter
    _xbee_buf[idx++] = 0x7E;

    //Length
    _xbee_buf[idx++] = 0x00;
    _xbee_buf[idx++] = 0x00;

    switch(_frame.frame_type){
        case TRANSMIT_REQUEST:{
            Tx_Req_Frame &tx_frame = static_cast <Tx_Req_Frame&>(_frame);

            //API Identifier
            tmp_checksum += TRANSMIT_REQUEST;
            _xbee_buf[idx++] = TRANSMIT_REQUEST;

            //Frame ID
            tmp_checksum += tx_frame.frame_id;
            _xbee_buf[idx++] = tx_frame.frame_id;

            //64-bit Destination Address
            tmp_checksum += (uint8_t)(tx_frame.dest_addr_64bit >> 56);
            _xbee_buf[idx++] = (uint8_t)(tx_frame.dest_addr_64bit >> 56);

            tmp_checksum += (uint8_t)(tx_frame.dest_addr_64bit >> 48);
            _xbee_buf[idx++] = (uint8_t)(tx_frame.dest_addr_64bit >> 48);

            tmp_checksum += (uint8_t)(tx_frame.dest_addr_64bit >> 40);
            _xbee_buf[idx++] = (uint8_t)(tx_frame.dest_addr_64bit >> 40);

            tmp_checksum += (uint8_t)(tx_frame.dest_addr_64bit >> 32);
            _xbee_buf[idx++] = (uint8_t)(tx_frame.dest_addr_64bit >> 32);

            tmp_checksum += (uint8_t)(tx_frame.dest_addr_64bit >> 24);
            _xbee_buf[idx++] = (uint8_t)(tx_frame.dest_addr_64bit >> 24);

            tmp_checksum += (uint8_t)(tx_frame.dest_addr_64bit >> 16);
            _xbee_buf[idx++] = (uint8_t)(tx_frame.dest_addr_64bit >> 16);

            tmp_checksum += (uint8_t)(tx_frame.dest_addr_64bit >> 8);
            _xbee_buf[idx++] = (uint8_t)(tx_frame.dest_addr_64bit >> 8);

            tmp_checksum += (uint8_t)tx_frame.dest_addr_64bit;
            _xbee_buf[idx++] = (uint8_t)tx_frame.dest_addr_64bit;

            //16-bit Destination Address
            tmp_checksum += (uint8_t)(tx_frame.dest_addr_16bit >> 8);
            _xbee_buf[idx++] = (uint8_t)(tx_frame.dest_addr_16bit >> 8);

            tmp_checksum += (uint8_t)tx_frame.dest_addr_16bit;
            _xbee_buf[idx++] = (uint8_t)tx_frame.dest_addr_16bit;

            //Broadcast Radius
            tmp_checksum += tx_frame.broadcast_radius;
            _xbee_buf[idx++] = tx_frame.broadcast_radius;

            //Transmit Options
            tmp_checksum += tx_frame.transmit_options;
            _xbee_buf[idx++] = tx_frame.transmit_options;

            //Payload Data
            for(uint8_t i = 0; i < tx_frame.payload_len; i++){
                if(tx_frame.payload_data[i] == 0x7E || tx_frame.payload_data[i] == 0x7D ||
                    tx_frame.payload_data[i] == 0x11 || tx_frame.payload_data[i] == 0x13){
                    tmp_checksum += 0x7D;
                    _xbee_buf[idx++] = 0x7D;
                    uint8_t escaped_byte = tx_frame.payload_data[i] ^ 0x20;
                    tmp_checksum += escaped_byte;
                    _xbee_buf[idx++] = escaped_byte;
                }else{
                    tmp_checksum += tx_frame.payload_data[i];
                    _xbee_buf[idx++] = tx_frame.payload_data[i];
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

        default:{

        }

    }






}
