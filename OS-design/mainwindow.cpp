#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    menu(0),
    dialog(0)
{
    ui->setupUi(this);
    ui->progressBar->setRange(0,100);
    ui->progressBar_2->setRange(0,100);
    ui->progressBar_3->setRange(0,100);
    ui->progressBar_4->setRange(0,100);
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, &QTreeWidget::customContextMenuRequested, this, &MainWindow::showMenu);

    QTableWidget& tablewidget=*ui->tableWidget_2;
    tablewidget.setColumnCount(4);
    //tablewidget.horizontalHeader()->setDefaultSectionSize(150);
//    QFont font=tablewidget.horizontalHeader()->font();
//    font.setBold(true);
//    tablewidget.horizontalHeader()->setFont(font);
    tablewidget.horizontalHeader()->setStretchLastSection(true);
    tablewidget.verticalHeader()->setDefaultSectionSize(10);
    //tablewidget.setFrameShape(QFrame::NoFrame);
    tablewidget.setShowGrid(false);
    tablewidget.verticalHeader()->setVisible(false);
    tablewidget.setSelectionMode(QAbstractItemView::ExtendedSelection);
    tablewidget.setSelectionBehavior(QAbstractItemView::SelectRows);
    tablewidget.setEditTriggers(QAbstractItemView::NoEditTriggers);
    tablewidget.setStyleSheet("selection-background-color:lightblue;");
    tablewidget.setItemDelegate(new NoFocusDelegate());

    monitor = new WorkerThread_monitor;
    connect(monitor, &WorkerThread_monitor::resultReady, this, &MainWindow::showProcess);
    connect(monitor, &WorkerThread_monitor::destroyed, monitor, &WorkerThread_monitor::deleteLater);
    monitor->start();

    cpu = new WorkerThread_cpu;
    connect(cpu, &WorkerThread_cpu::resultReady, this, &MainWindow::showCPU);
    connect(cpu, &WorkerThread_cpu::destroyed, cpu, &WorkerThread_cpu::deleteLater);
    cpu->start();

    fs = new FileSystem;
    buildTree(fs->rootDir, "/", 0);
    showCurDir();
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete fs;
}

void MainWindow::showProcess(int p_num)
{
    ui->listWidget->clear();
    for(int i = 0; i < p_num; ++i)
    {
        char state[256];
        sprintf(state, "%-40s%-40d%-40s%-30.2lf", monitor->ps[i].command, monitor->ps[i].pid, monitor->ps[i].u_name, monitor->ps[i].cpu_usage);
        ui->listWidget->addItem(QString(state));
    }

    QString memLabel = QString::number((monitor->ms.memtotal-monitor->ms.memfree)/(1024*1024), 'f', 1)+"GB, 共"+QString::number(monitor->ms.memtotal/(1024*1024), 'f', 1)+"GB";
    ui->label_5->setText(memLabel);
    ui->progressBar_5->setRange(0,monitor->ms.memtotal);
    ui->progressBar_5->setValue(monitor->ms.memtotal-monitor->ms.memfree);

    if(monitor->ns[0].enp_receive==0 && monitor->ns[0].wlp_receive==0) return;
    if(monitor->ns[1].enp_receive==monitor->ns[0].enp_receive)
    {
        long bytes_down = monitor->ns[1].wlp_receive-monitor->ns[0].wlp_receive;
        long bytes_up = monitor->ns[1].wlp_transmit-monitor->ns[0].wlp_transmit;
        double down = bytes_down/1, up = bytes_up/1;
        if(down>1024*1024) ui->downloadRate->setText(QString::number(down/(1024*1024),'f',1)+"MB/s");
        else if(down>1024) ui->downloadRate->setText(QString::number(down/(1024),'f',1)+"KB/s");
        else ui->downloadRate->setText(QString::number(down,'f',1)+"B/s");
        if(up>1024*1024) ui->uploadRate->setText(QString::number(up/(1024*1024),'f',1)+"MB/s");
        else if(up>1024) ui->uploadRate->setText(QString::number(up/(1024),'f',1)+"KB/s");
        else ui->uploadRate->setText(QString::number(up,'f',1)+"B/s");

        const long &receive = monitor->ns[1].wlp_receive, &transmit = monitor->ns[1].wlp_transmit;
        if(receive>1024*1024) ui->download->setText(QString::number(receive/(1024*1024),'f',1)+"MB");
        else if(receive>1024) ui->download->setText(QString::number(receive/(1024),'f',1)+"KB");
        else ui->download->setText(QString::number(receive,'f',1)+"字节");
        if(transmit>1024*1024) ui->upload->setText(QString::number(transmit/(1024*1024),'f',1)+"MB");
        else if(transmit>1024) ui->upload->setText(QString::number(transmit/(1024),'f',1)+"KB");
        else ui->upload->setText(QString::number(transmit,'f',1)+"字节");
    }
    else
    {
        long bytes_down = monitor->ns[1].enp_receive-monitor->ns[0].enp_receive;
        long bytes_up = monitor->ns[1].enp_transmit-monitor->ns[0].enp_transmit;
        double down = bytes_down/1, up = bytes_up/1;
        if(down>1024*1024) ui->downloadRate->setText(QString::number(down/(1024*1024),'f',1)+"MB/s");
        else if(down>1024) ui->downloadRate->setText(QString::number(down/(1024),'f',1)+"KB/s");
        else ui->downloadRate->setText(QString::number(down,'f',1)+"B/s");
        if(up>1024*1024) ui->uploadRate->setText(QString::number(up/(1024*1024),'f',1)+"MB/s");
        else if(up>1024) ui->uploadRate->setText(QString::number(up/(1024),'f',1)+"KB/s");
        else ui->uploadRate->setText(QString::number(up,'f',1)+"B/s");

        const long &receive = monitor->ns[1].enp_receive, &transmit = monitor->ns[1].enp_transmit;
        if(receive>1024*1024) ui->download->setText(QString::number(receive/(1024*1024),'f',1)+"MB");
        else if(receive>1024) ui->download->setText(QString::number(receive/(1024),'f',1)+"KB");
        else ui->download->setText(QString::number(receive,'f',1)+"字节");
        if(transmit>1024*1024) ui->upload->setText(QString::number(transmit/(1024*1024),'f',1)+"MB");
        else if(transmit>1024) ui->upload->setText(QString::number(transmit/(1024),'f',1)+"KB");
        else ui->upload->setText(QString::number(transmit,'f',1)+"字节");
    }
}

void MainWindow::showCPU()
{
    ui->progressBar->setValue(cpu->rate[0]*100);
    ui->progressBar_2->setValue(cpu->rate[1]*100);
    ui->progressBar_3->setValue(cpu->rate[2]*100);
    ui->progressBar_4->setValue(cpu->rate[3]*100);
    ui->progressBar->setFormat(QString("%1%").arg(QString::number(cpu->rate[0]*100, 'f', 1)));
    ui->progressBar_2->setFormat(QString("%1%").arg(QString::number(cpu->rate[1]*100, 'f', 1)));
    ui->progressBar_3->setFormat(QString("%1%").arg(QString::number(cpu->rate[2]*100, 'f', 1)));
    ui->progressBar_4->setFormat(QString("%1%").arg(QString::number(cpu->rate[3]*100, 'f', 1)));
}

void MainWindow::buildTree(iNode* curDir, char* fileName, QTreeWidgetItem* parent)
{    
    QTreeWidgetItem *treeItem;
    printf("Building file tree...\n");
    if(parent==0)
    {
        ui->treeWidget->clear();
        treeItem = new QTreeWidgetItem(ui->treeWidget);
        treeItem->setText(0, "/");
        //treeItem->setText(1, "根目录");
    }
    else
    {
        if(curDir->i_type==Dir && fileName[strlen(fileName)-1]!='/')
        {
            fileName[strlen(fileName)]='/';
            fileName[strlen(fileName)+1]='\0';
        }
        treeItem = new QTreeWidgetItem();
        treeItem->setText(0, fileName);
        //treeItem->setText(1, description);
        parent->addChild(treeItem);
    }
    if(curDir->i_type==Dir)
    {        
        for(int i=0;i<8;++i)
        {
            int blockNum=curDir->i_addr[i];
            if(1<=blockNum && blockNum<=block_num)
            {
                dirEntry* pe=(dirEntry*)fs->getBlockAddr(blockNum);
                for(int j=0;j<32;++j)
                {                    
                    int inode_num=pe->inode_num;
                    char *fileName=pe->fileName;
                    if(inode_num>0)
                    {
                        buildTree(&fs->iTbl.i[inode_num], fileName, treeItem);
                    }
                    else
                        return;
                    pe++;
                }
            }
        }
    }
}

void MainWindow::showCurDir()
{
    iNode* curDir=fs->curDir;
    showFile("..",0,-1,0);
    for(int i=0;i<8;++i)
    {
        dirEntry* pe=(dirEntry*)fs->getBlockAddr(curDir->i_addr[i]);
        for(int j=0;j<32;++j)
        {
            int inode_num=pe->inode_num;
            char* fileName=pe->fileName;
            if(inode_num>0)
            {
                iNode* inode=&fs->iTbl.i[inode_num];
                showFile(QString(fileName), inode->i_uid, inode->i_type, inode->i_size);
                pe++;
            }
            else
                return;
        }
    }
}

void MainWindow::showFile(QString& fileName, short uid, short type, long size)
{
    QTableWidget* tablewidget=ui->tableWidget_2;
    int row_count=tablewidget->rowCount();
    tablewidget->insertRow(row_count);
    QTableWidgetItem* item=new QTableWidgetItem();
    QTableWidgetItem* item1=new QTableWidgetItem();
    QTableWidgetItem* item2=new QTableWidgetItem();
    QTableWidgetItem* item3=new QTableWidgetItem();
    item->setText(fileName);
    item1->setText(QString::number(uid));
    if(type==Dir)
        item2->setText(QString("文件夹"));
    else
        item2->setText(QString("文档"));
    item3->setText(QString::number(size)+"B");
    tablewidget->setItem(row_count,0,item);
    tablewidget->setItem(row_count,1,item1);
    tablewidget->setItem(row_count,2,item2);
    tablewidget->setItem(row_count,3,item3);
    QColor color("gray");
    item1->setTextColor(color);
    item2->setTextColor(color);
    item3->setTextColor(color);
}

void MainWindow::showMenu(const QPoint& pos)
{
    if(menu)
    {
        delete menu;
        menu=0;
    }
    menu=new QMenu(ui->treeWidget);
    QAction* createDir=menu->addAction("新建文件夹");
    QAction* createFile=menu->addAction("新建文件");
    connect(createDir, &QAction::triggered, this, &MainWindow::newDir);
    connect(createFile, &QAction::triggered, this, &MainWindow::newFile);
    menu->exec(QCursor::pos());
}

void MainWindow::newDir()
{
    dialog=new Dialog(0, "请输入路径：");
    if(dialog->exec()==QDialog::Accepted && fs->changeDir(dialog->name)==0)
    {        
        free(dialog->name);
        delete dialog;
        dialog=new Dialog(0, "请输入文件夹名：");
        if(dialog->exec()==QDialog::Accepted && fs->createDir(dialog->name)==0)
        {
            free(dialog->name);
            buildTree(fs->rootDir, "/", 0);
        }
    }
}

void MainWindow::newFile()
{
    dialog=new Dialog(1, "请输入路径：");
    if(dialog->exec()==QDialog::Accepted && fs->changeDir(dialog->name)==0)
    {
        free(dialog->name);
        delete dialog;
        dialog=new Dialog(1, "请输入文件名：");
        if(dialog->exec()==QDialog::Accepted && fs->createFile(dialog->name)==0)
        {
            free(dialog->name);
            buildTree(fs->rootDir, "/", 0);
        }
    }
}
