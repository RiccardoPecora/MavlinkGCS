#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    ui->statusBar->showMessage("Ready...");
    qDebug("Ready");

    sp = new QSerialPort();
    fillPortsParameters();


    connect(ui->btnConnect,SIGNAL(clicked()),this,SLOT(serialConnect()));
    connect(ui->btnDisconnect,SIGNAL(clicked()),this,SLOT(serialDisconnect()));
    connect(ui->btnWrite,SIGNAL(clicked()),this,SLOT(serialWrite()));
    connect(ui->btnHeartBit,SIGNAL(clicked()),this,SLOT(sendMsg_HearBit()));
    connect(ui->btnBelugaPN_SN,SIGNAL(clicked()),this,SLOT(sendMsg_BelugaPNSN()));
    connect(sp,SIGNAL(readyRead()),this,SLOT(serialRead()));
    //connect(sp,SIGNAL(errorOccurred(QSerialPort::SerialPortError)),this,SLOT(serialError(QSerialPort::SerialPortError)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillPortsParameters()
{
    foreach (const QSerialPortInfo &port, QSerialPortInfo::availablePorts()) {
        ui->cboxPort->addItem(port.portName());
        ui->cboxPort->setCurrentIndex(5);
    }

    foreach (const qint32 baud, QSerialPortInfo::standardBaudRates()) {
        QString qStr = QString::number(baud);
        ui->baudRateBox->addItem(qStr);
        ui->baudRateBox->setCurrentIndex(12);
    }

    ui->dataBitsBox->addItem(QStringLiteral("5"), QSerialPort::Data5);
    ui->dataBitsBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    ui->dataBitsBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    ui->dataBitsBox->addItem(QStringLiteral("8"), QSerialPort::Data8);
    ui->dataBitsBox->setCurrentIndex(3);

    ui->parityBox->addItem(tr("None"), QSerialPort::NoParity);
    ui->parityBox->addItem(tr("Even"), QSerialPort::EvenParity);
    ui->parityBox->addItem(tr("Odd"), QSerialPort::OddParity);
    ui->parityBox->addItem(tr("Mark"), QSerialPort::MarkParity);
    ui->parityBox->addItem(tr("Space"), QSerialPort::SpaceParity);

    ui->stopBitsBox->addItem(QStringLiteral("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
    ui->stopBitsBox->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
#endif
    ui->stopBitsBox->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

    ui->flowControlBox->addItem(tr("None"), QSerialPort::NoFlowControl);
    ui->flowControlBox->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    ui->flowControlBox->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
}

void MainWindow::serialConnect()
{
    sp->setPortName(ui->cboxPort->currentText());
    sp->setBaudRate(QSerialPort::Baud9600);
    sp->setDataBits(QSerialPort::Data8);
    sp->setStopBits(QSerialPort::OneStop);
    sp->setParity(QSerialPort::NoParity);
    sp->setFlowControl(QSerialPort::NoFlowControl);

    ui->statusBar->showMessage("Porta: " + sp->portName()+ " Baudrate: " +  QString::number(sp->baudRate()), 5000);
    qDebug("Tentativo Apertura Porta...");

    try {
        sp->open(QSerialPort::ReadWrite);
        if(sp->isOpen()){
            qInfo() << "Porta seriale aperta";
            ui->btnConnect->setEnabled(false);
            ui->btnDisconnect->setEnabled(true);

            uint8_t buf[MAVLINK_MAX_PACKET_LEN];
            uint16_t buf_len;
            sp->write((char*)buf, (qint64)buf_len);
        }
    }catch (exception e) {
        qWarning() << "Errore durante l'apertura della porta: " << e.what();
    }

}

void MainWindow::serialDisconnect()
{
    try {
        sp->close();
        if(!sp->isOpen()){
            qInfo() << "Porta seriale chiusa";
            ui->btnConnect->setEnabled(true);
            ui->btnDisconnect->setEnabled(false);
        }
    }catch (exception e) {
        qWarning() << "Errore durante la chiusura della porta: " << e.what();
    }
}


void MainWindow::serialError(QSerialPort::SerialPortError error)
{
    ui->statusBar->showMessage("Errore Apertura Porta");
    ui->btnConnect->setEnabled(true);
    ui->btnDisconnect->setEnabled(false);
    qDebug("Errore Apertura Porta");
}

void MainWindow::serialWrite(){
    uint8_t* buf = (uint8_t*)ui->linEdWrite->text().toUtf8().data();
    uint16_t buf_len = ui->linEdWrite->text().toUtf8().size();
    sp->write((char*)buf, (qint64)buf_len);

}

void MainWindow::sendMsg_HearBit()
{
    mavlink_heartbeat_t heartbit_msg;
    heartbit_msg.autopilot = MAV_AUTOPILOT_ARDUPILOTMEGA;
    heartbit_msg.base_mode = MAV_MODE_FLAG_STABILIZE_ENABLED;
    heartbit_msg.custom_mode = COPTER_MODE_STABILIZE;
    heartbit_msg.system_status = MAV_STATE_STANDBY;
    heartbit_msg.type = MAV_TYPE_QUADROTOR;

    uint8_t sys_id = (uint8_t)ui->le_sys_id->text().toUInt();
    uint8_t comp_id = (uint8_t)ui->le_comp_id->text().toUInt();

    mavlink_message_t msg;
    mavlink_msg_heartbeat_encode(sys_id, comp_id, &msg, &heartbit_msg);

    uint8_t buf[MAX_PACKET_LENGHT];
    mavlink_msg_to_send_buffer(buf, &msg);
    //QByteArray test = QByteArray::fromRawData((char*)buf, msg.len + OTHER_MSG_BYTE);
    //ui->txtEdRead->append(test.toHex());
    sp->write((char*)buf, (qint64)(msg.len + OTHER_MSG_BYTE));
}

void MainWindow::sendMsg_Attitude()
{

}

void MainWindow::sendMsg_BelugaPNSN()
{
    mavlink_beluga_pn_sn_t beluga_pn_sn;
    QString pn = "SV01++";
    QString sn = "SN-01";

    for(uint8_t i = 0; i < pn.length(); i++){
        beluga_pn_sn.PN[i] = pn.at(i).toLatin1();
    }
    for(uint8_t i = 0; i < sn.length(); i++){
        beluga_pn_sn.SN[i] = sn.at(i).toLatin1();
    }

    uint8_t sys_id = (uint8_t)ui->le_sys_id->text().toUInt();
    uint8_t comp_id = (uint8_t)ui->le_comp_id->text().toUInt();

    mavlink_message_t msg;
    mavlink_msg_beluga_pn_sn_encode(sys_id, comp_id, &msg, &beluga_pn_sn);

    uint8_t buf[MAX_PACKET_LENGHT];
    mavlink_msg_to_send_buffer(buf, &msg);
    sp->write((char*)buf, (qint64)(msg.len + OTHER_MSG_BYTE));
}


void MainWindow::serialRead()
{
    // qInfo() << "Bytes Letti: " << buf;
    //QByteArray data = sp->readAll();
    QByteArray buf = sp->readAll() ;
    foreach (char byte_read, buf) {
        if(xbee.parse_xbee_frame(byte_read, msg)){
            ui->txtEdRead->append(msg.toHex());
            uint16_t len = msg.size();
            parse_mavlink_msg((uint8_t*)msg.data(), len);
            msg.clear();
        }
    }
}

void MainWindow::parse_mavlink_msg(uint8_t *buf, uint16_t &buf_len){
    mavlink_message_t msg;
    mavlink_status_t status;

    for (uint16_t i = 0; i < buf_len; i++) {
        if (mavlink_parse_char(0, buf[i], &msg, &status)) {
            handle_mavlink_msg(msg);
        }
    }
}

void MainWindow::handle_mavlink_msg(mavlink_message_t &msg){

    // Handle message
    switch (msg.msgid) {
        case MAVLINK_MSG_ID_HEARTBEAT:  // #0: Heartbeat
        {
            // E.g. read GCS heartbeat and go into
            // comm lost mode if timer times out
            mavlink_heartbeat_t heartbeat;
            mavlink_msg_heartbeat_decode(&msg, &heartbeat);

            ui->leMavVers->setText(QString::number(heartbeat.mavlink_version));
            ui->leAutopilot->setText(QString::number(heartbeat.autopilot));
            ui->leBasemode->setText(QString::number(heartbeat.base_mode));

    #ifdef DEBUG
            ui->txtEdRead->append("Heartbeat - Mavlink Version: " + QString::number(heartbeat.mavlink_version));
            ui->txtEdRead->append("Heartbeat - Autopilot: " + QString::number(heartbeat.autopilot));
            ui->txtEdRead->append("Heartbeat - Base_Mode: " + QString::number(heartbeat.base_mode));
            ui->txtEdRead->append("Heartbeat - System-ID: " + QString::number(msg.sysid));
            ui->txtEdRead->append("Heartbeat - Component-ID: " + QString::number(msg.compid));
            cout << "Heartbeat - Mavlink Version: " << to_string(heartbeat.mavlink_version) << endl;
            cout << "Heartbeat - Autopilot: " << to_string(heartbeat.autopilot) << endl;
            cout << "Heartbeat - Base_Mode: " << to_string(heartbeat.base_mode) << endl;
            cout << "Heartbeat - System-ID: " << to_string(msg.sysid) << endl;
            cout << "Heartbeat - Component-ID: " << to_string(msg.compid) << endl;
    #endif // DEBUG

            break;
        }


        case MAVLINK_MSG_ID_SYS_STATUS:  // #1: SYS_STATUS
        {
            mavlink_sys_status_t sys_status;
            mavlink_msg_sys_status_decode(&msg, &sys_status);


            ui->leBatLev->setText(QString::number(sys_status.battery_remaining));
    #ifdef DEBUG
            ui->txtEdRead->append("System Status - Battery remaining: " + QString::number(sys_status.battery_remaining));
            printf("System Status - Battery remaining: %d \n", sys_status.battery_remaining);
    #endif // DEBUG

            break;
        }


        case MAVLINK_MSG_ID_PARAM_VALUE:  // #22: PARAM_VALUE
        {
            mavlink_param_value_t param_value;
            mavlink_msg_param_value_decode(&msg, &param_value);
            break;
        }


        case MAVLINK_MSG_ID_RAW_IMU:  // #27: RAW_IMU
        {
            mavlink_raw_imu_t raw_imu;
            mavlink_msg_raw_imu_decode(&msg, &raw_imu);


    #ifdef DEBUG
            ui->txtEdRead->append("Raw IMU - Xaccel: " + QString::number(raw_imu.xacc));
            ui->txtEdRead->append("Raw IMU - Yaccel: " + QString::number(raw_imu.yacc));
            ui->txtEdRead->append("Raw IMU - Zaccel: " + QString::number(raw_imu.zacc));
            ui->txtEdRead->append("Raw IMU - Xgyro: " + QString::number(raw_imu.xgyro));
            ui->txtEdRead->append("Raw IMU - Ygyro: " + QString::number(raw_imu.ygyro));
            ui->txtEdRead->append("Raw IMU - Zgyro: " + QString::number(raw_imu.zgyro));
            ui->txtEdRead->append("Raw IMU - Xmag: " + QString::number(raw_imu.xmag));
            ui->txtEdRead->append("Raw IMU - Ymag: " + QString::number(raw_imu.ymag));
            ui->txtEdRead->append("Raw IMU - Zmag: " + QString::number(raw_imu.zmag));

            printf("Raw IMU - Xaccel: %d \n", raw_imu.xacc);
            printf("Raw IMU - Yaccel: %d \n", raw_imu.yacc);
            printf("Raw IMU - zaccel: %d \n", raw_imu.zacc);
            printf("Raw IMU - Xgyro: %d \n", raw_imu.xgyro);
            printf("Raw IMU - Ygyro: %d \n", raw_imu.ygyro);
            printf("Raw IMU - Zgyro: %d \n", raw_imu.zgyro);
            printf("Raw IMU - Xmag: %d \n", raw_imu.xmag);
            printf("Raw IMU - Ymag: %d \n", raw_imu.ymag);
            printf("Raw IMU - Zmag: %d \n", raw_imu.zmag);
    #endif // DEBUG
            break;
        }


        case MAVLINK_MSG_ID_ATTITUDE:  // #30
        {
            mavlink_attitude_t attitude;
            mavlink_msg_attitude_decode(&msg, &attitude);


    #ifdef DEBUG
            ui->txtEdRead->append("Attitude Roll: " + QString::number(attitude.roll));
            ui->txtEdRead->append("Attitude Pitch: " + QString::number(attitude.pitch));
            ui->txtEdRead->append("Attitude Yaw: " + QString::number(attitude.yaw));
            printf("Attitude Roll: %f \n", attitude.roll);
            printf("Attitude Pitch: %f \n", attitude.pitch);
            printf("Attitude Yaw: %f \n", attitude.yaw);
    #endif // DEBUG
            break;
        }


        case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:  // #33: GLOBAL_POSITION_INT
        {
            mavlink_global_position_int_t glob_pos;
            mavlink_msg_global_position_int_decode(&msg, &glob_pos);



                ui->leLatitude->setText(QString::number(glob_pos.lat));
                ui->leLongitude->setText(QString::number(glob_pos.lon));
                ui->leAltitude->setText(QString::number(glob_pos.alt));
    #ifdef DEBUG
                ui->txtEdRead->append("Latitude: " + QString::number(glob_pos.lat));
                ui->txtEdRead->append("Longitude: " + QString::number(glob_pos.lon));
                ui->txtEdRead->append("Altitude: " + QString::number(glob_pos.alt));
                printf("Latitude: %d \n", glob_pos.lat);
                printf("Longitude: %d \n", glob_pos.lon);
                printf("Altitude: %d \n", glob_pos.alt);
    #endif // DEBUG
            break;
        }

        case MAVLINK_MSG_ID_BELUGA_PN_SN:  // #60000: Beluga PN SN
        {
            mavlink_beluga_pn_sn_t beluga_pn_sn;
            mavlink_msg_beluga_pn_sn_decode(&msg, &beluga_pn_sn);
            string pn(beluga_pn_sn.PN, 10);
            string sn(beluga_pn_sn.SN, 10);

            // ui->leMavVers->setText(QString::number(heartbeat.mavlink_version));
            // ui->leAutopilot->setText(QString::number(heartbeat.autopilot));
            // ui->leBasemode->setText(QString::number(heartbeat.base_mode));

#ifdef DEBUG
            ui->txtEdRead->append("Beluga PN SN - Part Number: " + QString::fromLatin1(beluga_pn_sn.PN));
            ui->txtEdRead->append("Beluga PN SN - Serial Number: " + QString::fromLatin1(beluga_pn_sn.SN));

            cout << "Beluga PN SN - Part Number: " << pn << endl;
            cout << "Beluga PN SN - Serial Number: " << sn << endl;

#endif // DEBUG

            break;
        }

    //     case MAVLINK_MSG_ID_MISSION_REQUEST:  // #40: MISSION_REQUEST
    //     {
    //         mavlink_mission_request_t miss_req;
    //         mavlink_msg_mission_request_decode(&msg, &miss_req);

    // #ifdef DEBUG
    //             printf("Sequence: %d \n", miss_req.seq);
    // #endif // DEBUG

    //         // Send MISSION_ITEM_INT msg
    //         send_mav_miss_item_msg(miss_buf_wp[miss_req.seq]);

    //         break;
    //     }

    //     case MAVLINK_MSG_ID_MISSION_ACK:  // #47: MISSION_ACK
    //     {
    //         mavlink_mission_ack_t miss_ack;
    //         mavlink_msg_mission_ack_decode(&msg, &miss_ack);

    //         if (miss_ack.type == MAV_MISSION_ACCEPTED) {
    //                 cout << "MISSION ACK - MAV_MISSION_ACCEPTED: " << to_string(miss_ack.type) << endl;
    //         }
    //         else {
    //                 cout << "MISSION ACK - MAV_MISSION_ERROR: " << to_string(miss_ack.type) << endl;
    //         }
    //         break;
    //     }

    //     case MAVLINK_MSG_ID_MISSION_COUNT:  // #44: MISSION_COUNT
    //     {
    //         mavlink_mission_count_t miss_cnt;
    //         mavlink_msg_mission_count_decode(&msg, &miss_cnt);

    // #ifdef DEBUG
    //             cout << "Mission Count: " << to_string(miss_cnt.count) << endl;
    // #endif // DEBUG

    //         count = miss_cnt.count;

    //         if (count) {
    //             seq = 0;

    //             // Send MISSION_REQ_INT msg
    //             send_mav_miss_req_int_msg(1, 0, MAV_MISSION_TYPE_MISSION, seq);
    //         }
    //         break;
    //     }

    //     case MAVLINK_MSG_ID_MISSION_ITEM_INT:  // #73: MISSION_ITEM_INT
    //     {
    //         mavlink_mission_item_int_t miss_itm_int;
    //         mavlink_msg_mission_item_int_decode(&msg, &miss_itm_int);

    //         if (miss_itm_int.seq == seq) {
    //             miss_recv_buf_wp.push_back(miss_itm_int);
    //             seq++;
    //         }

    //         if (seq < count) {
    //             // Send MISSION_REQ_INT msg
    //             send_mav_miss_req_int_msg(1, 0, MAV_MISSION_TYPE_MISSION, seq);
    //         }
    //         else if (seq == count) {
    //             // Send MISSION_ACK msg
    //             send_mav_miss_ack_msg(1, 0, MAV_MISSION_TYPE_MISSION, MAV_MISSION_ACCEPTED);

    //                 cout << "MISSION WP DOWNLOAD COMPLETE" << endl;
    //         }

    //         break;
    //     }


        default: {
            break;
        }
    }
}

