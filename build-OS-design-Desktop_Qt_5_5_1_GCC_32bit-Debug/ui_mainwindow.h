/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *horizontalSpacer;
    QToolBox *toolBox;
    QWidget *page;
    QTextBrowser *textBrowser;
    QGroupBox *groupBox_4;
    QProgressBar *progressBar_6;
    QGroupBox *groupBox_5;
    QLabel *label_10;
    QWidget *page_2;
    QWidget *page_3;
    QLineEdit *lineEdit;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QDialogButtonBox *buttonBox;
    QWidget *page_4;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTableWidget *tableWidget;
    QListWidget *listWidget;
    QWidget *tab_2;
    QGroupBox *groupBox;
    QProgressBar *progressBar;
    QProgressBar *progressBar_2;
    QProgressBar *progressBar_3;
    QProgressBar *progressBar_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QGroupBox *groupBox_2;
    QProgressBar *progressBar_5;
    QLabel *label_5;
    QGroupBox *groupBox_3;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *downloadRate;
    QLabel *uploadRate;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *download;
    QLabel *upload;
    QWidget *tab_3;
    QWidget *page_5;
    QTreeWidget *treeWidget;
    QTableWidget *tableWidget_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(619, 610);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(-1, -11, 621, 591));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        toolBox = new QToolBox(verticalLayoutWidget);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 619, 378));
        textBrowser = new QTextBrowser(page);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(10, 0, 241, 371));
        groupBox_4 = new QGroupBox(page);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(260, 0, 351, 181));
        progressBar_6 = new QProgressBar(groupBox_4);
        progressBar_6->setObjectName(QStringLiteral("progressBar_6"));
        progressBar_6->setGeometry(QRect(40, 90, 261, 23));
        progressBar_6->setValue(24);
        groupBox_5 = new QGroupBox(page);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(259, 190, 351, 181));
        label_10 = new QLabel(groupBox_5);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(50, 70, 251, 41));
        toolBox->addItem(page, QString::fromUtf8("\344\273\273\345\212\241\344\270\200\357\274\2323\344\270\252\345\271\266\345\217\221\350\277\233\347\250\213"));
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 619, 378));
        toolBox->addItem(page_2, QString::fromUtf8("\344\273\273\345\212\241\344\272\214\357\274\232\346\267\273\345\212\240\347\263\273\347\273\237\350\260\203\347\224\250"));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        page_3->setGeometry(QRect(0, 0, 619, 378));
        lineEdit = new QLineEdit(page_3);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(170, 66, 291, 31));
        label_11 = new QLabel(page_3);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(170, 160, 251, 21));
        label_12 = new QLabel(page_3);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(110, 70, 51, 21));
        label_13 = new QLabel(page_3);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(70, 160, 81, 21));
        buttonBox = new QDialogButtonBox(page_3);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(220, 260, 176, 27));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        toolBox->addItem(page_3, QString::fromUtf8("\344\273\273\345\212\241\344\270\211\357\274\232\346\267\273\345\212\240\350\256\276\345\244\207\351\251\261\345\212\250"));
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        page_4->setGeometry(QRect(0, 0, 619, 378));
        tabWidget = new QTabWidget(page_4);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 621, 381));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tableWidget = new QTableWidget(tab);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(-10, 0, 631, 31));
        tableWidget->horizontalHeader()->setDefaultSectionSize(157);
        listWidget = new QListWidget(tab);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(0, 30, 621, 321));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 611, 111));
        groupBox->setFlat(false);
        progressBar = new QProgressBar(groupBox);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(40, 40, 211, 21));
        progressBar->setValue(24);
        progressBar_2 = new QProgressBar(groupBox);
        progressBar_2->setObjectName(QStringLiteral("progressBar_2"));
        progressBar_2->setGeometry(QRect(320, 80, 211, 21));
        progressBar_2->setValue(24);
        progressBar_3 = new QProgressBar(groupBox);
        progressBar_3->setObjectName(QStringLiteral("progressBar_3"));
        progressBar_3->setGeometry(QRect(40, 80, 211, 21));
        progressBar_3->setValue(24);
        progressBar_4 = new QProgressBar(groupBox);
        progressBar_4->setObjectName(QStringLiteral("progressBar_4"));
        progressBar_4->setGeometry(QRect(320, 40, 211, 21));
        progressBar_4->setValue(24);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(260, 40, 41, 17));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(260, 80, 41, 17));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(540, 40, 41, 17));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(540, 80, 41, 17));
        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(-1, 110, 611, 101));
        progressBar_5 = new QProgressBar(groupBox_2);
        progressBar_5->setObjectName(QStringLiteral("progressBar_5"));
        progressBar_5->setGeometry(QRect(40, 60, 251, 23));
        progressBar_5->setValue(24);
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(310, 60, 201, 17));
        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(-1, 230, 611, 121));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(40, 40, 71, 17));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(310, 40, 71, 17));
        downloadRate = new QLabel(groupBox_3);
        downloadRate->setObjectName(QStringLiteral("downloadRate"));
        downloadRate->setGeometry(QRect(140, 40, 101, 17));
        uploadRate = new QLabel(groupBox_3);
        uploadRate->setObjectName(QStringLiteral("uploadRate"));
        uploadRate->setGeometry(QRect(410, 40, 91, 17));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(40, 80, 81, 17));
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(310, 80, 81, 17));
        download = new QLabel(groupBox_3);
        download->setObjectName(QStringLiteral("download"));
        download->setGeometry(QRect(140, 80, 111, 17));
        upload = new QLabel(groupBox_3);
        upload->setObjectName(QStringLiteral("upload"));
        upload->setGeometry(QRect(410, 80, 111, 17));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        tabWidget->addTab(tab_3, QString());
        toolBox->addItem(page_4, QString::fromUtf8("\344\273\273\345\212\241\345\233\233\357\274\232\347\263\273\347\273\237\347\233\221\350\247\206\345\231\250"));
        page_5 = new QWidget();
        page_5->setObjectName(QStringLiteral("page_5"));
        page_5->setGeometry(QRect(0, 0, 619, 378));
        treeWidget = new QTreeWidget(page_5);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(0, 0, 161, 381));
        tableWidget_2 = new QTableWidget(page_5);
        tableWidget_2->setObjectName(QStringLiteral("tableWidget_2"));
        tableWidget_2->setGeometry(QRect(160, 0, 461, 381));
        toolBox->addItem(page_5, QString::fromUtf8("\344\273\273\345\212\241\344\272\224\357\274\232\346\250\241\346\213\237\346\226\207\344\273\266\347\263\273\347\273\237"));

        verticalLayout->addWidget(toolBox);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        toolBox->setCurrentIndex(2);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "CPU\345\210\251\347\224\250\347\216\207", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "\345\275\223\345\211\215\346\227\266\351\227\264", 0));
        label_10->setText(QString());
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("MainWindow", "\344\273\273\345\212\241\344\270\200\357\274\2323\344\270\252\345\271\266\345\217\221\350\277\233\347\250\213", 0));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("MainWindow", "\344\273\273\345\212\241\344\272\214\357\274\232\346\267\273\345\212\240\347\263\273\347\273\237\350\260\203\347\224\250", 0));
        label_11->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_12->setText(QApplication::translate("MainWindow", "\350\276\223\345\205\245\357\274\232", 0));
        label_13->setText(QApplication::translate("MainWindow", "myDevice\357\274\232", 0));
        toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("MainWindow", "\344\273\273\345\212\241\344\270\211\357\274\232\346\267\273\345\212\240\350\256\276\345\244\207\351\251\261\345\212\250", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "\350\277\233\347\250\213\345\220\215", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "ID", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "\347\224\250\346\210\267", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "% CPU", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\350\277\233\347\250\213", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "CPU\345\210\251\347\224\250\347\216\207", 0));
        label->setText(QApplication::translate("MainWindow", "CPU0", 0));
        label_2->setText(QApplication::translate("MainWindow", "CPU2", 0));
        label_3->setText(QApplication::translate("MainWindow", "CPU1", 0));
        label_4->setText(QApplication::translate("MainWindow", "CPU3", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\345\206\205\345\255\230\345\210\251\347\224\250\347\216\207", 0));
        label_5->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\347\275\221\347\273\234", 0));
        label_6->setText(QApplication::translate("MainWindow", "\346\255\243\345\234\250\346\216\245\346\224\266", 0));
        label_7->setText(QApplication::translate("MainWindow", "\346\255\243\345\234\250\345\217\221\351\200\201", 0));
        downloadRate->setText(QApplication::translate("MainWindow", "0.0B/s", 0));
        uploadRate->setText(QApplication::translate("MainWindow", "0.0B/s", 0));
        label_8->setText(QApplication::translate("MainWindow", "\346\200\273\350\256\241\345\267\262\346\216\245\346\224\266", 0));
        label_9->setText(QApplication::translate("MainWindow", "\346\200\273\347\273\223\345\267\262\345\217\221\351\200\201", 0));
        download->setText(QApplication::translate("MainWindow", "0\345\255\227\350\212\202", 0));
        upload->setText(QApplication::translate("MainWindow", "0\345\255\227\350\212\202", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\350\265\204\346\272\220", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "\346\226\207\344\273\266\347\263\273\347\273\237", 0));
        toolBox->setItemText(toolBox->indexOf(page_4), QApplication::translate("MainWindow", "\344\273\273\345\212\241\345\233\233\357\274\232\347\263\273\347\273\237\347\233\221\350\247\206\345\231\250", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "\346\226\207\344\273\266\346\240\221", 0));
        toolBox->setItemText(toolBox->indexOf(page_5), QApplication::translate("MainWindow", "\344\273\273\345\212\241\344\272\224\357\274\232\346\250\241\346\213\237\346\226\207\344\273\266\347\263\273\347\273\237", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
