#ifndef COMM_SERIAL_H
#define COMM_SERIAL_H

#include <QtSerialPort/qserialport.h>
#include <QSerialPortInfo>
#include <QDebug>
#include <QObject>
#include <QTime>
#include <QThread>
#include "Comm_Base.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//MACROS
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define DEBUG
#define MAX_LENGHT 100

struct serial_port_config{
    QString port_name;
    QSerialPort::BaudRate baudrate;
    QSerialPort::DataBits databits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopbits;
    QSerialPort::FlowControl flowctrl;
};

namespace COMM {

    class Comm_Serial : public Comm_Base
    {
        Q_OBJECT
    public:
        Comm_Serial();
        int8_t connect(struct serial_port_config &config);
        int8_t close();
        int8_t send(uint8_t*& _ptr_buf, uint16_t& _buf_len);//const QByteArray &outBuf

    private:
        QSerialPort *seriale;
        QByteArray buffer[MAX_LENGHT];
        int8_t receive(uint8_t*& _ptr_buf, uint16_t& _buf_len);

    private slots:
        void serialRead();
        void readChannelFinished();
        void channelReadyRead(int channel);


    signals:
        void connected();
        void disconnected();
        void error();
        void received(QByteArray buf);
        void timeout();

    };


}
#endif // COMM_SERIAL_H
