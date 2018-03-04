#include "monitor.h"
#include "ui_monitor.h"
#include <QDebug>

Monitor::Monitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Monitor)
{
    ui->setupUi(this);

    worker = new WorkerThread_monitor;
    connect(worker, &WorkerThread_monitor::resultReady, this, &Monitor::handleResult);
    connect(worker, &WorkerThread_monitor::destroyed, worker, &WorkerThread_monitor::deleteLater);
    worker->start();
}

Monitor::~Monitor()
{
    delete ui;
}

void Monitor::handleResult(int p_num)
{
    for(int i = 0; i < p_num; ++i)
    {
        char state[256];
        sprintf(state, "%-30s%-30s%-35lf%-30d%-30lld", worker->ps[i].command, worker->ps[i].u_name, worker->ps[i].cpu_usage, worker->ps[i].pid, worker->ps[i].mem_occupy);
        ui->listWidget->addItem(QString(state));
    }
}
