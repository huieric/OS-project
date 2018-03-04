#include "showcpu.h"
#include "ui_showcpu.h"

ShowCPU::ShowCPU(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowCPU)
{
    ui->setupUi(this);
    ui->rateBar->setRange(0, 100);

    WorkerThread_cpu *worker = new WorkerThread_cpu;
    connect(worker, &WorkerThread_cpu::resultReady, this, &ShowCPU::handleResult);
    connect(worker, &WorkerThread_cpu::destroyed, worker, &WorkerThread_cpu::deleteLater);
    worker->start();
}

ShowCPU::~ShowCPU()
{
    delete ui;
}

void ShowCPU::handleResult(const double rate)
{
    char rateText[30];
    sprintf(rateText, "%.2lf%%", rate * 100);
    ui->rateBar->setValue(rate * 100);
    ui->rateLabel->setText(rateText);
}
