#ifndef SHOWTIME_H
#define SHOWTIME_H

#include <QWidget>
#include <QThread>
#include <stdio.h>
#include <time.h>

namespace Ui {
class ShowTime;
}

class ShowTime : public QWidget
{
    Q_OBJECT

public:
    explicit ShowTime(QWidget *parent = 0);
    ~ShowTime();

public slots:
    void handleResult(const QString& s);

private:
    Ui::ShowTime *ui;
};

class WorkerThread : public QThread
{
    Q_OBJECT

public:
    void run()
    {
        while(1)
        {
            getTime();
            sleep(1);
        }
    }

public slots:
    void getTime()
    {
        time_t t = time(0);
        char tmp[64];
        strftime(tmp, sizeof(tmp), "%Y/%m/%d %X %A 本年第%j天 %z",localtime(&t));
        QString cur_time = QString(tmp);
        emit resultReady(cur_time);
    }

signals:
    void resultReady(const QString& s);
};

#endif // SHOWTIME_H
