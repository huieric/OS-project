#include "show_time.h"
#include "show_cpu.h"
#include "show_sum.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Show_cpu w1;
    w1.show();
    Show_time w2;
    w2.show();
    Show_sum w3;
    w3.show();

    return a.exec();
}
