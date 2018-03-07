#include "edit.h"
#include "ui_edit.h"

Edit::Edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edit)
{
    ui->setupUi(this);

    //ui->buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("保存");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("关闭");
}

Edit::~Edit()
{
    delete ui;
}

void Edit::on_buttonBox_accepted()
{
    char* origin=ui->textEdit->toPlainText().toLatin1().data();
    text=(char*)malloc(strlen(origin)+1);
    strcpy(text, origin);
}

void Edit::setTextEdit(char *buf)
{
    ui->textEdit->append(buf);
}
