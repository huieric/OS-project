#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(int type, QString prompt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    if(type==0)
    {
        setWindowTitle("新建文件夹");
        ui->label->setText(prompt);
    }
    else
    {
        setWindowTitle("新建文件");
        ui->label->setText(prompt);
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    name=(char*)malloc(30);
    strcpy(name, ui->lineEdit->text().toLatin1().data());
}
