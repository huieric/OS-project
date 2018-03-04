#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <stdio.h>
#include "monitor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void showProcess(int p_num);
    void showCPU();
    void showFile();

private:
    Ui::MainWindow *ui;
    WorkerThread_monitor *monitor;
    WorkerThread_cpu *cpu;
    void addTreeChild(QTreeWidgetItem *parent, const QString &name, const QString &description);
};

#endif // MAINWINDOW_H
