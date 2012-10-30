#ifndef TICKER_H
#define TICKER_H

#include <QThread>
#include <QDebug>

class Ticker : public QThread {
    quint64 interval;
    quint8 currentTickNumber;

    Ticker();

protected:
    void run() {
        while (currentTickNumber <= 100) {
            qDebug() << currentTickNumber++;
            usleep(interval);
        }
    }

public:
    Ticker(quint64 interval):interval(interval) {
        currentTickNumber = 0;
        this->start();
    }

};

#endif // TICKER_H
