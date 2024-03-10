#include "xbee_module.h"

Xbee_module::Xbee_module(QObject *parent)
    : QObject{parent}
{}

void Xbee_module::setAddr64bit(uint64_t _addr_64bit)
{
    this->addr_64bit = _addr_64bit;
}

uint64_t Xbee_module::getAddr64bit() const
{
    return this->addr_64bit;
}

void Xbee_module::setAddr16bit(uint16_t _addr_16bit)
{
    this->addr_16bit = _addr_16bit;
}

uint16_t Xbee_module::getAddr16bit() const
{
    return this->addr_64bit;
}

void Xbee_module::setNodeIdString(char _node_id_string[])
{
    for(uint8_t i = 0; i < MAX_NODE_ID_BYTE; i++){
        this->node_id_string[i] = _node_id_string[i];
    }

}

char* Xbee_module::getNodeIdString()
{
    return this->node_id_string;
}
