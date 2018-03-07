#ifndef EDIT_H
#define EDIT_H

#include <QDialog>
#include <QPushButton>
#include <QDebug>

namespace Ui {
class Edit;
}

class Edit : public QDialog
{
    Q_OBJECT

public:
    explicit Edit(QWidget *parent = 0);
    ~Edit();
    void setTextEdit(char* buf);
    char* text;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Edit *ui;
};

#endif // EDIT_H
