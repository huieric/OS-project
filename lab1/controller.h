#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QMainWindow>

namespace Ui {
class Controller;
}

class Controller : public QMainWindow
{
    Q_OBJECT

public:
    explicit Controller(QWidget *parent = 0);
    ~Controller();   

private slots:   
    void on_process_clicked();

    void on_closeProcess_clicked();

    void on_monitor_clicked();

    void on_closeMonitor_clicked();

private:
    Ui::Controller *ui;

signals:
    void display();
    void closeWin();
    void monitor();
    void closeMon();
};

#endif // CONTROLLER_H
