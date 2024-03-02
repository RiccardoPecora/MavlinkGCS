#ifndef COMM_BASE
#define COMM_BASE

#include <iostream>
#include <inttypes.h>
#include <QObject>

using namespace std;

namespace COMM{

class Comm_Base : public QObject
{
    Q_OBJECT
public:
	Comm_Base();
	virtual int8_t init();
	virtual int8_t begin();
	virtual int8_t connect();
	virtual int8_t close();
	virtual int8_t encode(const uint8_t* _cmd, uint32_t* _param, uint8_t& _param_num, uint8_t* _param_dim, uint8_t*& _ptr_payload, uint8_t& _payload_length);
	virtual int8_t decode(uint8_t*& _ptr_payload, uint8_t& _payload_length);
	virtual int8_t send(uint8_t*& _ptr_buf, uint16_t& _buf_len);
	virtual int8_t receive(uint8_t*& _ptr_buf, uint16_t& _buf_len);


};

}
#endif //COMM_BASE
