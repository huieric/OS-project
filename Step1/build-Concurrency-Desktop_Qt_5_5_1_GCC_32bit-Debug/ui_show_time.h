/********************************************************************************
** Form generated from reading UI file 'show_time.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOW_TIME_H
#define UI_SHOW_TIME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CurrentTime
{
public:
    QLabel *timeLabel;

    void setupUi(QWidget *CurrentTime)
    {
        if (CurrentTime->objectName().isEmpty())
            CurrentTime->setObjectName(QStringLiteral("CurrentTime"));
        CurrentTime->resize(400, 300);
        timeLabel = new QLabel(CurrentTime);
        timeLabel->setObjectName(QStringLiteral("timeLabel"));
        timeLabel->setGeometry(QRect(70, 130, 251, 31));

        retranslateUi(CurrentTime);

        QMetaObject::connectSlotsByName(CurrentTime);
    } // setupUi

    void retranslateUi(QWidget *CurrentTime)
    {
        CurrentTime->setWindowTitle(QApplication::translate("CurrentTime", "Show_time", 0));
        timeLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CurrentTime: public Ui_CurrentTime {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOW_TIME_H
