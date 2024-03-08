#ifndef WORKER_TICK_H
#define WORKER_TICK_H

#include <QObject>
#include <QThread>

class WorkerTick : public QThread
{
    Q_OBJECT

public:
    explicit WorkerTick(QObject *parent = nullptr);
    void run() override;
signals:
    void sgnTick1s();
};

#endif // WORKER_TICK_H
