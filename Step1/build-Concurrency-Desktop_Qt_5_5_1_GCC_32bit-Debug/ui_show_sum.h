/********************************************************************************
** Form generated from reading UI file 'show_sum.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOW_SUM_H
#define UI_SHOW_SUM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Show_sum
{
public:

    void setupUi(QWidget *Show_sum)
    {
        if (Show_sum->objectName().isEmpty())
            Show_sum->setObjectName(QStringLiteral("Show_sum"));
        Show_sum->resize(400, 300);

        retranslateUi(Show_sum);

        QMetaObject::connectSlotsByName(Show_sum);
    } // setupUi

    void retranslateUi(QWidget *Show_sum)
    {
        Show_sum->setWindowTitle(QApplication::translate("Show_sum", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class Show_sum: public Ui_Show_sum {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOW_SUM_H
