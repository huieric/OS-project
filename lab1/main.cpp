#include "showtime.h"
#include "showsum.h"
#include "showcpu.h"
#include "controller.h"
#include "monitor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShowTime w_time;
    ShowSum w_sum;
    ShowCPU w_cpu;
    Monitor monitor;
    Controller controller;
    controller.show();

    QObject::connect(&controller, &Controller::display, &w_time, &ShowTime::show);
    QObject::connect(&controller, &Controller::display, &w_sum, &ShowSum::show);
    QObject::connect(&controller, &Controller::display, &w_cpu, &ShowCPU::show);
    QObject::connect(&controller, &Controller::closeWin, &w_time, &ShowTime::close);
    QObject::connect(&controller, &Controller::closeWin, &w_sum, &ShowSum::close);
    QObject::connect(&controller, &Controller::closeWin, &w_cpu, &ShowCPU::close);
    QObject::connect(&controller, &Controller::monitor, &monitor, &Monitor::show);
    QObject::connect(&controller, &Controller::closeMon, &monitor, &Monitor::close);

    return a.exec();
}
