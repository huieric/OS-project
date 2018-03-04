#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setRange(0,100);
    ui->progressBar_2->setRange(0,100);
    ui->progressBar_3->setRange(0,100);
    ui->progressBar_4->setRange(0,100);

    monitor = new WorkerThread_monitor;
    connect(monitor, &WorkerThread_monitor::resultReady, this, &MainWindow::showProcess);
    connect(monitor, &WorkerThread_monitor::destroyed, monitor, &WorkerThread_monitor::deleteLater);
    monitor->start();

    cpu = new WorkerThread_cpu;
    connect(cpu, &WorkerThread_cpu::resultReady, this, &MainWindow::showCPU);
    connect(cpu, &WorkerThread_cpu::destroyed, cpu, &WorkerThread_cpu::deleteLater);
    cpu->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showProcess(int p_num)
{
    ui->listWidget->clear();
    for(int i = 0; i < p_num; ++i)
    {
        char state[256];
        sprintf(state, "%-40s%-40d%-40s%-30.2lf", monitor->ps[i].command, monitor->ps[i].pid, monitor->ps[i].u_name, monitor->ps[i].cpu_usage);
        ui->listWidget->addItem(QString(state));
    }

    QString memLabel = QString::number((monitor->ms.memtotal-monitor->ms.memfree)/(1024*1024), 'f', 1)+"GB, 共"+QString::number(monitor->ms.memtotal/(1024*1024), 'f', 1)+"GB";
    ui->label_5->setText(memLabel);
    ui->progressBar_5->setRange(0,monitor->ms.memtotal);
    ui->progressBar_5->setValue(monitor->ms.memtotal-monitor->ms.memfree);

    if(monitor->ns[0].enp_receive==0 && monitor->ns[0].wlp_receive==0) return;
    if(monitor->ns[1].enp_receive==monitor->ns[0].enp_receive)
    {
        long bytes_down = monitor->ns[1].wlp_receive-monitor->ns[0].wlp_receive;
        long bytes_up = monitor->ns[1].wlp_transmit-monitor->ns[0].wlp_transmit;
        double down = bytes_down/1, up = bytes_up/1;
        if(down>1024*1024) ui->downloadRate->setText(QString::number(down/(1024*1024),'f',1)+"MB/s");
        else if(down>1024) ui->downloadRate->setText(QString::number(down/(1024),'f',1)+"KB/s");
        else ui->downloadRate->setText(QString::number(down,'f',1)+"B/s");
        if(up>1024*1024) ui->uploadRate->setText(QString::number(up/(1024*1024),'f',1)+"MB/s");
        else if(up>1024) ui->uploadRate->setText(QString::number(up/(1024),'f',1)+"KB/s");
        else ui->uploadRate->setText(QString::number(up,'f',1)+"B/s");

        const long &receive = monitor->ns[1].wlp_receive, &transmit = monitor->ns[1].wlp_transmit;
        if(receive>1024*1024) ui->download->setText(QString::number(receive/(1024*1024),'f',1)+"MB");
        else if(receive>1024) ui->download->setText(QString::number(receive/(1024),'f',1)+"KB");
        else ui->download->setText(QString::number(receive,'f',1)+"字节");
        if(transmit>1024*1024) ui->upload->setText(QString::number(transmit/(1024*1024),'f',1)+"MB");
        else if(transmit>1024) ui->upload->setText(QString::number(transmit/(1024),'f',1)+"KB");
        else ui->upload->setText(QString::number(transmit,'f',1)+"字节");
    }
    else
    {
        long bytes_down = monitor->ns[1].enp_receive-monitor->ns[0].enp_receive;
        long bytes_up = monitor->ns[1].enp_transmit-monitor->ns[0].enp_transmit;
        double down = bytes_down/1, up = bytes_up/1;
        if(down>1024*1024) ui->downloadRate->setText(QString::number(down/(1024*1024),'f',1)+"MB/s");
        else if(down>1024) ui->downloadRate->setText(QString::number(down/(1024),'f',1)+"KB/s");
        else ui->downloadRate->setText(QString::number(down,'f',1)+"B/s");
        if(up>1024*1024) ui->uploadRate->setText(QString::number(up/(1024*1024),'f',1)+"MB/s");
        else if(up>1024) ui->uploadRate->setText(QString::number(up/(1024),'f',1)+"KB/s");
        else ui->uploadRate->setText(QString::number(up,'f',1)+"B/s");

        const long &receive = monitor->ns[1].enp_receive, &transmit = monitor->ns[1].enp_transmit;
        if(receive>1024*1024) ui->download->setText(QString::number(receive/(1024*1024),'f',1)+"MB");
        else if(receive>1024) ui->download->setText(QString::number(receive/(1024),'f',1)+"KB");
        else ui->download->setText(QString::number(receive,'f',1)+"字节");
        if(transmit>1024*1024) ui->upload->setText(QString::number(transmit/(1024*1024),'f',1)+"MB");
        else if(transmit>1024) ui->upload->setText(QString::number(transmit/(1024),'f',1)+"KB");
        else ui->upload->setText(QString::number(transmit,'f',1)+"字节");
    }
}

void MainWindow::showCPU()
{
    ui->progressBar->setValue(cpu->rate[0]*100);
    ui->progressBar_2->setValue(cpu->rate[1]*100);
    ui->progressBar_3->setValue(cpu->rate[2]*100);
    ui->progressBar_4->setValue(cpu->rate[3]*100);
    ui->progressBar->setFormat(QString("%1%").arg(QString::number(cpu->rate[0]*100, 'f', 1)));
    ui->progressBar_2->setFormat(QString("%1%").arg(QString::number(cpu->rate[1]*100, 'f', 1)));
    ui->progressBar_3->setFormat(QString("%1%").arg(QString::number(cpu->rate[2]*100, 'f', 1)));
    ui->progressBar_4->setFormat(QString("%1%").arg(QString::number(cpu->rate[3]*100, 'f', 1)));
}

void MainWindow::addTreeChild(QTreeWidgetItem *parent, const QString &name, const QString &description)
{
        // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
        QTreeWidgetItem *treeItem = new QTreeWidgetItem();

        // QTreeWidgetItem::setText(int column, const QString & text)
        treeItem->setText(0, name);
        treeItem->setText(1, description);

        // QTreeWidgetItem::addChild(QTreeWidgetItem * child)
        parent->addChild(treeItem);
}

void MainWindow::showFile()
{

}
