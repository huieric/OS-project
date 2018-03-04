/********************************************************************************
** Form generated from reading UI file 'show_cpu.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOW_CPU_H
#define UI_SHOW_CPU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Show_cpu
{
public:

    void setupUi(QWidget *Show_cpu)
    {
        if (Show_cpu->objectName().isEmpty())
            Show_cpu->setObjectName(QStringLiteral("Show_cpu"));
        Show_cpu->resize(400, 300);

        retranslateUi(Show_cpu);

        QMetaObject::connectSlotsByName(Show_cpu);
    } // setupUi

    void retranslateUi(QWidget *Show_cpu)
    {
        Show_cpu->setWindowTitle(QApplication::translate("Show_cpu", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class Show_cpu: public Ui_Show_cpu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOW_CPU_H
