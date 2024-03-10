#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#define MAX_PACKET_LENGHT 255
#define OTHER_MSG_BYTE 12
#define XBEE3_COORDINATOR_64BIT_ADDRESS 0x0013A200423D9053
#define XBEE3_ROUTER_64BIT_ADDRESS 0x0013A200423D8B87
#define XBEE3_END_DEVICE_64BIT_ADDRESS 0x0013A200423D90D5

#define XBEE2_UAV1_64BIT_ADDRESS 0x0013A2004092D7EE
#define XBEE2_UAV2_64BIT_ADDRESS 0x0013A2004061626D
#define XBEE2_BASE_STATION_64BIT_ADDRESS 0x0013A2004092D7E4

#include <QMainWindow>
#include <QtSerialPort>
#include <QSerialPortInfo>
#include "lib/Comm_Serial.h"
#include "lib/mavlink_beluga/beluga/mavlink.h"
#include "xbee_lib/xbee_helper.h"
#include"xbee_lib/xbee_module.h"
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
    Xbee_Helper xbee_helper;
    QByteArray msg;
    WorkerTick *worker_tick;
    QList<Xbee_module*> xbee_discovery_list;


    void fillPortsParameters();
    void parse_mavlink_msg(uint8_t *buf, uint16_t &buf_len);
    void handle_mavlink_msg(mavlink_message_t &msg);
    void heartbit_loop();
    bool decode(QByteArray& _msg);


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
