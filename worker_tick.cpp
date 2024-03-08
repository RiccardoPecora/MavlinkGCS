#include "worker_tick.h"


WorkerTick::WorkerTick(QObject *parent){}

void WorkerTick::run() {
    while(true){
        this->sleep(1);
        emit sgnTick1s();
    }
}
