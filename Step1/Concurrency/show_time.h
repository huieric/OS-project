#ifndef SHOW_TIME_H
#define SHOW_TIME_H

#include <QWidget>
#include <QThread>
#include <QTimer>
#include <stdio.h>
#include <time.h>

namespace Ui {
class Show_time;
}

class Show_time : public QWidget
{
    Q_OBJECT

public:
    explicit Show_time(QWidget *parent = 0);
    ~Show_time();

public slots:
    void handleResult(const QString& s);

private:
    Ui::Show_time *ui;
};

class WorkerThread : public QThread
{
    Q_OBJECT

private:
    QTimer timer;

public:
    void run();

public slots:
    void getTime();

signals:
    void resultReady(const QString& s);
};

void WorkerThread::run()
{
    connect(&timer, &QTimer::timeout, this, &WorkerThread::getTime);
    getTime();
}

void WorkerThread::getTime()
{
    time_t t = time(0);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y/%m/%d %X %A 本年第%j天 %z",localtime(&t));
    QString cur_time = QString(tmp);
    emit resultReady(cur_time);
    timer.start();
}

#endif // SHOW_TIME_H
