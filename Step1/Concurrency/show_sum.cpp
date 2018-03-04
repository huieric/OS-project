#include "show_sum.h"
#include "ui_show_sum.h"

Show_sum::Show_sum(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Show_sum)
{
    ui->setupUi(this);
}

Show_sum::~Show_sum()
{
    delete ui;
}
