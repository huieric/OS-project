#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTreeWidget>
#include <QMenu>
#include <QAction>
#include <stdio.h>
#include "monitor.h"
#include "filesystem.h"
#include "dialog.h"
#include "no_focus_delegate.h"

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
    void showTableMenu(const QPoint& pos);
    void newDir();
    void newFile();
    void newDir_table();
    void newFile_table();
    void tableDoubleClickedSlots(QModelIndex index);

private:
    Ui::MainWindow *ui;
    WorkerThread_monitor *monitor;
    WorkerThread_cpu *cpu;
    FileSystem *fs;
    QMenu* menu;
    QMenu* table_menu;
    Dialog* dialog;
    void buildTree(iNode* curDir, char* fileName, QTreeWidgetItem* parent);
    void showCurDir();
    void showFile(QString& fileName, short uid, short type, long size);
};

#endif // MAINWINDOW_H
