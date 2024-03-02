#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#define MAX_PACKET_LENGHT 255
#define OTHER_MSG_BYTE 12

#include <QMainWindow>
#include <QtSerialPort>
#include <QSerialPortInfo>
#include <QThread>
#include <mutex>
#include "lib/Comm_Serial.h"
//#include "lib/mavlink_ric/v2.0/ardupilotmega/mavlink.h"
#include "lib/mavlink_beluga/beluga/mavlink.h"
#include "xbee.h"

// const uint8_t  SYS_ID = ;

// const uint8_t  HEARTBIT__MAVLINK_VERSION = 3;
// const uint8_t  HEARTBIT__AUTOPILOT = 4;
// const uint8_t  HEARTBIT__BASE_MODE = MAV_MODE_STABILIZE_DISARMED;

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
    QByteArray data_buf, msg;
    uint frame_in_progress = 0;
    XBEE::FRAME_STATE frame_state = XBEE::START_DELIMITER;
    uint xbee_frame_idx = 0;
    uint xbee_frame_len = 0;

    void fillPortsParameters();
    void parse_mavlink_msg(uint8_t *buf, uint16_t &buf_len);
    void handle_mavlink_msg(mavlink_message_t &msg);

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
