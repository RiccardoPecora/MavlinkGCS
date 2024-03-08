#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#define MAX_PACKET_LENGHT 255
#define OTHER_MSG_BYTE 12
#define COORDINATOR_64BIT_ADDRESS 0x0013A200423D9053
#define ROUTER_64BIT_ADDRESS 0x0013A200423D8B87
#define END_DEVICE_64BIT_ADDRESS 0x0013A200423D90D5


#include <QMainWindow>
#include <QtSerialPort>
#include <QSerialPortInfo>
#include <thread>

#include <mutex>
#include "lib/Comm_Serial.h"
//#include "lib/mavlink_ric/v2.0/ardupilotmega/mavlink.h"
#include "lib/mavlink_beluga/beluga/mavlink.h"
#include "xbee.h"
#include "worker_tick.h"


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSerialPort *sp;
    struct serial_port_config config {0};
    XBEE xbee;
    QByteArray msg;
    WorkerTick *worker_tick;

    void fillPortsParameters();
    void parse_mavlink_msg(uint8_t *buf, uint16_t &buf_len);
    void handle_mavlink_msg(mavlink_message_t &msg);
    void heartbit_loop();


private slots:
    void serialConnect();
    void serialDisconnect();
    void serialError(QSerialPort::SerialPortError error);
    void serialWrite();
    void serialRead();
    void sendMsg_HearBit();
    void sendMsg_Attitude();
    void sendMsg_BelugaPNSN();


};


#endif // MAINWINDOW_H
