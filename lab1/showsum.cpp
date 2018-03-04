#include "showsum.h"
#include "ui_showsum.h"

ShowSum::ShowSum(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowSum),
    row(0)
{
    ui->setupUi(this);

    WorkerThread_sum *worker = new WorkerThread_sum;
    connect(worker, &WorkerThread_sum::resultReady, this, &ShowSum::handleResult);
    connect(worker, &WorkerThread_sum::destroyed, worker, &WorkerThread_sum::deleteLater);
    worker->start();
}

ShowSum::~ShowSum()
{
    delete ui;
}

void ShowSum::handleResult(const QString& s)
{
    ui->sumLabel->insertPlainText(s);
    ui->sumLabel->moveCursor(QTextCursor::Start);
}
