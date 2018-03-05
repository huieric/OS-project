#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QMenu>
#include <QAction>
#include <stdio.h>
#include "monitor.h"
#include "filesystem.h"
#include "dialog.h"

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
    void showMenu(const QPoint& pos);
    void newDir();
    void newFile();

private:
    Ui::MainWindow *ui;
    WorkerThread_monitor *monitor;
    WorkerThread_cpu *cpu;
    FileSystem *fs;
    QMenu* menu;
    Dialog* dialog;
    void buildTree(iNode* curDir, char* fileName, QTreeWidgetItem* parent);
};

#endif // MAINWINDOW_H
