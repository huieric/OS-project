#include "show_cpu.h"
#include "ui_show_cpu.h"

Show_cpu::Show_cpu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Show_cpu)
{
    ui->setupUi(this);
}

Show_cpu::~Show_cpu()
{
    delete ui;
}
