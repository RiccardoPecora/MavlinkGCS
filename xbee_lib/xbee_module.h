#ifndef XBEE_MODULE_H
#define XBEE_MODULE_H

#include <QObject>

#define MAX_NODE_ID_BYTE 20

class Xbee_module : public QObject
{
    Q_OBJECT
public:
    explicit Xbee_module(QObject *parent = nullptr);
    void setAddr64bit(uint64_t _addr_64bit);
    uint64_t getAddr64bit() const;
    void setAddr16bit(uint16_t _addr_16bit);
    uint16_t getAddr16bit() const;
    void setNodeIdString(char _node_id_string[MAX_NODE_ID_BYTE]);
    char* getNodeIdString();

signals:

private:
    uint64_t addr_64bit;
    uint16_t addr_16bit;
    char node_id_string[MAX_NODE_ID_BYTE] {0};

};


#endif // XBEE_MODULE_H
