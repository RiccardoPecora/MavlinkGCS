#include "Comm_Serial.h"

COMM::Comm_Serial::Comm_Serial()
{
    seriale = new QSerialPort();
    QObject::connect(seriale,SIGNAL(readyRead()),this,SLOT(serialRead()));
    QObject::connect(seriale,SIGNAL(readChannelFinished()),this,SLOT(readChannelFinished()));
    QObject::connect(seriale,SIGNAL(channelReadyRead(int)),this,SLOT(channelReadyRead(int)));

}

int8_t COMM::Comm_Serial::connect(struct serial_port_config &config)
{
    //seriale = new QSerialPort();
    seriale->setPortName(config.port_name);
    seriale->setBaudRate(config.baudrate);
    seriale->setDataBits(config.databits);
    seriale->setStopBits(config.stopbits);
    seriale->setParity(config.parity);
    seriale->setFlowControl(config.flowctrl);

    seriale->open(QSerialPort::ReadWrite);
    qDebug("Tentativo Apertura Porta...");
    if(seriale->isOpen()){

        qDebug("Connessione Stabilita");
        emit connected();
    }else{
        qDebug("Errore Apertura Porta");
        emit error();
    }
    return (seriale->isOpen());
}

int8_t COMM::Comm_Serial::close()
{
    seriale->close();
    if(!seriale->isOpen()){
        qDebug("Disconnessione Effettuata");
        emit disconnected();
    }else{
        qDebug("Errore Chiusura Porta");
        emit error();
    }
    return (!seriale->isOpen());
}

void COMM::Comm_Serial::serialRead()
{
    QByteArray buf = seriale->readAll();
   // qInfo() << "Bytes Letti: " << buf;
    //qInfo()<< "Comm Module Thread: " << QThread::currentThread();
    emit received(buf);
}

int8_t COMM::Comm_Serial::receive(uint8_t*& _ptr_buf, uint16_t& _buf_len)
{
    QByteArray requestData;
    bool data_available = false;
    if (seriale->bytesAvailable()) {
        data_available = true;

        // read request
        requestData.append(seriale->readAll());
        // while (seriale->waitForReadyRead(50)){
        //     requestData.append(seriale->readAll());
        // }
    } /*else {
        return 0;
        // emit timeout(tr("Wait read request timeout %1")
        //                  .arg(QTime::currentTime().toString()));
    }*/

    if(data_available){
        _ptr_buf = (uint8_t*)requestData.data();
        _buf_len = requestData.size();
        return 1;
    }else{
        return 0;
    }
}

int8_t COMM::Comm_Serial::send(uint8_t*& _ptr_buf, uint16_t& _buf_len){  //const QByteArray &outBuf
    // outBuf.append(ui->linEdWrite->text().toUtf8());
    QByteArray outBuf;
    outBuf.setRawData((char*)_ptr_buf, _buf_len);
    qint64 byteWrite = seriale->write(outBuf);
    qDebug() << "Bytes Trasferiti: " + std::to_string(byteWrite);
    return 1;
}

void COMM::Comm_Serial::readChannelFinished(){
    qInfo() << "Read Channel Finished";
}

void COMM::Comm_Serial::channelReadyRead(int channel){
    qInfo() << "Channel Ready To Read: " << channel;
}


