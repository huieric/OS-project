#include "showtime.h"
#include "ui_showtime.h"

ShowTime::ShowTime(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowTime)
{
    ui->setupUi(this);

    WorkerThread *worker = new WorkerThread;
    connect(worker, &WorkerThread::resultReady, this, &ShowTime::handleResult);
    connect(worker, &WorkerThread::destroyed, worker, &WorkerThread::deleteLater);
    worker->start();
}

ShowTime::~ShowTime()
{
    delete ui;
}

void ShowTime::handleResult(const QString& s)
{
    ui->timeLabel->setText(s);
}
