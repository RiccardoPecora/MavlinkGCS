#ifndef MAVLINKWRAPPER_H
#define MAVLINKWRAPPER_H

#include <QObject>
#include "lib/Mavlink_8.h"

class MavlinkWrapper : public QObject
{
    Q_OBJECT
public:
    explicit MavlinkWrapper(QObject *parent = nullptr);
    //MAVLINK::GCS_Mavlink gcs;
private:

    uint16_t recvbuflen = 1024;
    uint8_t* recvbuf = new uint8_t(recvbuflen);
    mutex m_cout;

signals:




};

#endif // MAVLINKWRAPPER_H
