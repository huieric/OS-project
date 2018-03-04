#include "show_time.h"
#include "ui_show_time.h"

Show_time::Show_time(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Show_time)
{
    ui->setupUi(this);
    WorkerThread *worker = new WorkerThread;
    connect(worker, &WorkerThread::resultReady, this, &Show_time::handleResult);
    connect(worker, &WorkerThread::destroyed, worker, &WorkerThread::deleteLater);
    worker->start();
}

Show_time::~Show_time()
{
    delete ui;
}

void Show_time::handleResult(const QString& s)
{
    ui->timeLabel->setText(s);
}
