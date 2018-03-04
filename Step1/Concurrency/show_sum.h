#ifndef SHOW_SUM_H
#define SHOW_SUM_H

#include <QWidget>

namespace Ui {
class Show_sum;
}

class Show_sum : public QWidget
{
    Q_OBJECT

public:
    explicit Show_sum(QWidget *parent = 0);
    ~Show_sum();

private:
    Ui::Show_sum *ui;
};

#endif // SHOW_SUM_H
