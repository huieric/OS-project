#ifndef MONITOR_H
#define MONITOR_H

#include <QWidget>
#include <QThread>
#include <QDebug>
#define MAX_SIZE 1000

namespace Ui {
class Monitor;
}

typedef struct
{
    int pid;
    int uid;
    double cpu_usage;
    char command[100];
    char u_name[50];
    long long mem_occupy;
}p_State;

class WorkerThread_monitor : public QThread
{
    Q_OBJECT

public:
    p_State ps[MAX_SIZE]={{1,0,0.3,"p1","huieric",1000}};
    void run()
    {
        emit resultReady(1);
    }

signals:
    void resultReady(int p_num);
};

class Monitor : public QWidget
{
    Q_OBJECT

public:
    explicit Monitor(QWidget *parent = 0);
    ~Monitor();

public:
    void handleResult(int p_num);

private:
    Ui::Monitor *ui;
    WorkerThread_monitor *worker;
};

#endif // MONITOR_H
