#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(int type, QString prompt, QWidget *parent = 0);
    ~Dialog();
    char* name;

private slots:


private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
