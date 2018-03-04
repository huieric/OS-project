#ifndef SHOW_CPU_H
#define SHOW_CPU_H

#include <QWidget>

namespace Ui {
class Show_cpu;
}

class Show_cpu : public QWidget
{
    Q_OBJECT

public:
    explicit Show_cpu(QWidget *parent = 0);
    ~Show_cpu();

private:
    Ui::Show_cpu *ui;
};

#endif // SHOW_CPU_H
