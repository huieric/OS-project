#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    menu(0),
    table_menu(0),
    dialog(0)
{
    ui->setupUi(this);
    ui->progressBar->setRange(0,100);
    ui->progressBar_2->setRange(0,100);
    ui->progressBar_3->setRange(0,100);
    ui->progressBar_4->setRange(0,100);
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, &QTreeWidget::customContextMenuRequested, this, &MainWindow::showMenu);
    ui->tableWidget_2->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget_2, &QTableWidget::customContextMenuRequested, this, &MainWindow::showTableMenu);
    connect(ui->tableWidget_2, &QTableWidget::doubleClicked, this, &MainWindow::tableDoubleClickedSlots);

    QTableWidget& tablewidget=*ui->tableWidget_2;
    tablewidget.setColumnCount(4);
    //tablewidget.horizontalHeader()->setDefaultSectionSize(150);
//    QFont font=tablewidget.horizontalHeader()->font();
//    font.setBold(true);
//    tablewidget.horizontalHeader()->setFont(font);
    tablewidget.horizontalHeader()->setStretchLastSection(true);
    tablewidget.verticalHeader()->setDefaultSectionSize(25);
    //tablewidget.setFrameShape(QFrame::NoFrame);
    tablewidget.setShowGrid(false);
    tablewidget.verticalHeader()->setVisible(false);
    tablewidget.setSelectionMode(QAbstractItemView::ExtendedSelection);
    tablewidget.setSelectionBehavior(QAbstractItemView::SelectRows);
    tablewidget.setEditTriggers(QAbstractItemView::NoEditTriggers);
    tablewidget.setStyleSheet("selection-background-color:lightblue;");
    //tablewidget.setItemDelegate(new NoFocusDelegate());
    QStringList header;
    header<<QString("名称")<<QString("用户")<<QString("类型")<<QString("大小");
    ui->tableWidget_2->setHorizontalHeaderLabels(header);

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

    p_CPU=new QProcess;
    p_Sum=new QProcess;
    p_Time=new QProcess;
    connect(p_CPU, &QProcess::readyRead, this, &MainWindow::readCPU);
    connect(p_Sum, &QProcess::readyRead, this, &MainWindow::readSum);
    connect(p_Time, &QProcess::readyRead, this, &MainWindow::readTime);
    p_CPU->start("./showCPU");
    p_Sum->start("./showSum");
    p_Time->start("./showTime");

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("安装");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("卸载");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete fs;
}

void MainWindow::readCPU()
{
    char temp[10];
    strcpy(temp, p_CPU->readAll().data());
    temp[strlen(temp)-1]='\0';
//    qDebug() << temp;
    double utilization=QString(temp).toDouble()*100;
    ui->progressBar_6->setRange(0,100);
    ui->progressBar_6->setValue(utilization);
    ui->progressBar_6->setFormat(QString::number(utilization,'f',1)+"%");
}

void MainWindow::readSum()
{
    char temp[30];
    strcpy(temp, p_Sum->readAll().data());
    temp[strlen(temp)-1]='\0';
    ui->textBrowser->append(QString(temp));
}

void MainWindow::readTime()
{
    ui->label_10->setText(QString(p_Time->readAll()));
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
    for(int i=ui->tableWidget_2->rowCount()-1;i>=0;--i)
        ui->tableWidget_2->removeRow(i);
    QString fileName=" . .";
    showFile(fileName,0,-1,0);
    for(int i=0;i<8;++i)
    {
        int blockNum=curDir->i_addr[i];
        if(1<=blockNum && blockNum<=block_num)
        {
            dirEntry* pe=(dirEntry*)fs->getBlockAddr(blockNum);
            for(int j=0;j<32;++j)
            {
                int inode_num=pe->inode_num;
                fileName=pe->fileName;
                if(inode_num>0)
                {
                    iNode* inode=&fs->iTbl.i[inode_num];
                    showFile(fileName, inode->i_uid, inode->i_type, inode->i_size);
                    pe++;
                }
                else
                    return;
            }
        }
    }
}

void MainWindow::showFile(QString& fileName, short uid, short type, long size)
{
    QTableWidget* tablewidget=ui->tableWidget_2;
    int row_count=tablewidget->rowCount();
    tablewidget->insertRow(row_count);
    if(type==-1)
    {
        QTableWidgetItem* item=new QTableWidgetItem();
        item->setText(fileName);
        item->setTextAlignment(Qt::AlignCenter);
        tablewidget->setItem(row_count,0,item);
        return;
    }
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
    item->setTextAlignment(Qt::AlignCenter);
    item1->setTextAlignment(Qt::AlignCenter);
    item2->setTextAlignment(Qt::AlignCenter);
    item3->setTextAlignment(Qt::AlignCenter);
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

void MainWindow::showTableMenu(const QPoint &pos)
{
    if(table_menu)
    {
        delete table_menu;
        table_menu=0;
    }
    table_menu=new QMenu(ui->tableWidget_2);
    QAction* action_create_folder=new QAction(ui->tableWidget_2);
    QAction* action_create_file=new QAction(ui->tableWidget_2);
    //QAction* action_rename=new QAction(ui->tableWidget_2);
    QAction* action_delete=new QAction(ui->tableWidget_2);
    action_create_folder->setText("新建文件夹");
    action_create_file->setText("新建文件");
    //action_rename->setText("删除");
    action_delete->setText("删除");
    connect(action_delete, &QAction::triggered, this, &MainWindow::deleteFile);
    connect(action_create_folder, &QAction::triggered, this, &MainWindow::newDir_table);
    connect(action_create_file, &QAction::triggered, this, &MainWindow::newFile_table);
    QTableWidgetItem* item=ui->tableWidget_2->itemAt(pos);
    if(item!=0)
    {
        table_menu->addAction(action_delete);
        //table_menu->addAction(action_rename);
        file_name=ui->tableWidget_2->item(item->row(), 0)->text();
    }
    else
    {
        table_menu->addAction(action_create_folder);
        table_menu->addAction(action_create_file);        
    }
    table_menu->exec(QCursor::pos());
}

void MainWindow::deleteFile()
{
    qDebug() << file_name;
    if(fs->remove(file_name.toLatin1().data())==0)
    {
        showCurDir();
        buildTree(fs->rootDir, "/", 0);
    }
}

void MainWindow::newDir_table()
{
    dialog=new Dialog(0, "请输入文件夹名：");
    if(dialog->exec()==QDialog::Accepted && fs->createDir(dialog->name)==0)
    {
        free(dialog->name);
        buildTree(fs->rootDir, "/", 0);
        showCurDir();
    }
}

void MainWindow::newFile_table()
{
    dialog=new Dialog(1, "请输入文件名：");
    if(dialog->exec()==QDialog::Accepted && fs->createFile(dialog->name)==0)
    {
        free(dialog->name);
        buildTree(fs->rootDir, "/", 0);
        showCurDir();
    }
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
            showCurDir();
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
            showCurDir();
        }
    }
}

void MainWindow::tableDoubleClickedSlots(QModelIndex index)
{
    int row=index.row();
    QString file_name=ui->tableWidget_2->item(row, 0)->text();
    char* fileName=file_name.toLatin1().data();
    if(strcmp(fileName," . .")==0 && fs->curDir==fs->rootDir)
    {
        return;
    }
    if(strcmp(fileName," . .")==0 && fs->changeDir("..")==0)
    {
        showCurDir();
        return;
    }
    for(int i=0;i<8;++i)
    {
        dirEntry* pe=(dirEntry*)fs->getBlockAddr(fs->curDir->i_addr[i]);
        for(int j=0;j<32;++j)
        {
            if(pe->inode_num==0) return;
            if(strcmp(pe->fileName, fileName)==0)
            {
                iNode& inode=fs->iTbl.i[pe->inode_num];
                if(inode.i_type==Dir)
                {
                    if(fs->changeDir(fileName)==0)
                    {
                        showCurDir();
                        fs->pwd();
                    }
                }
                else
                {
                    fs->open(fileName);
                    showCurDir();
                }
                return;
            }
            pe++;
        }
    }
}

void MainWindow::on_buttonBox_accepted()
{
    QStringList options;
    QProcess* p=new QProcess;
    options << "-c" << "insmod /home/huieric/Document/OS-project/Step3/myDrive.ko";
    p->start("/bin/bash",options);
    p->waitForFinished();
    qDebug() << QTextCodec::codecForLocale()->toUnicode(p->readAllStandardError());
    options.clear();
    options << "-c" << "cat /proc/devices | grep myDevice";
    p->start("/bin/bash",options);
    p->waitForFinished();
    char temp[10];
    char* dev_mesg=p->readAll().data();
    qDebug() << dev_mesg;
    char* pt=strchr(dev_mesg, ' ');
    strncpy(temp, dev_mesg, pt-dev_mesg);
    temp[pt-dev_mesg]='\0';
    qDebug() << temp;
    options.clear();
    options << "-c" << QString("mknod /dev/myDevice c ")+temp+" 0";
    p->start("/bin/bash",options);
    p->waitForFinished();
    qDebug() << QTextCodec::codecForLocale()->toUnicode(p->readAllStandardError());
}

void MainWindow::on_buttonBox_rejected()
{
    QStringList options;
    QProcess* p=new QProcess;
    options << "-c" << "rmmod /home/huieric/Document/OS-project/Step3/myDrive.ko";
    p->start("/bin/bash",options);
    p->waitForFinished();
    qDebug() << QTextCodec::codecForLocale()->toUnicode(p->readAllStandardError());
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    qDebug() << arg1;
    char buf[MAX_SIZE];
    char* in;
    int fd = open("/dev/myDevice", O_RDWR | O_NONBLOCK);
    if(fd != -1)
    {
        read(fd, buf, sizeof(buf));
        ui->label_11->setText(buf);

//        in=arg1.toLatin1().data();
//        write(fd, in, sizeof(in));

//        read(fd, buf, sizeof(buf));
//        ui->label_11->setText(buf);

       //close(fd);
    }
    else
    {
        ui->label_11->setText("Open myDevice failed!\n");
    }
}
