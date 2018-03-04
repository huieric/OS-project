#include "controller.h"
#include "ui_controller.h"

Controller::Controller(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Controller)
{
    ui->setupUi(this);
}

Controller::~Controller()
{
    delete ui;
}

void Controller::on_process_clicked()
{
    emit display();
}

void Controller::on_closeProcess_clicked()
{
    emit closeWin();
}

void Controller::on_monitor_clicked()
{
    emit monitor();
}

void Controller::on_closeMonitor_clicked()
{
    emit closeMon();
}
