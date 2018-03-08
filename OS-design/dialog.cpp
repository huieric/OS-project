#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QString windowText, QString prompt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle(windowText);
    ui->label->setText(prompt);
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
