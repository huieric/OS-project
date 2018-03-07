/********************************************************************************
** Form generated from reading UI file 'hedit.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HEDIT_H
#define UI_HEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Hedit
{
public:
    QTextEdit *textEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *Hedit)
    {
        if (Hedit->objectName().isEmpty())
            Hedit->setObjectName(QStringLiteral("Hedit"));
        Hedit->resize(600, 423);
        textEdit = new QTextEdit(Hedit);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(30, 20, 531, 361));
        buttonBox = new QDialogButtonBox(Hedit);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(390, 390, 176, 27));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(Hedit);

        QMetaObject::connectSlotsByName(Hedit);
    } // setupUi

    void retranslateUi(QWidget *Hedit)
    {
        Hedit->setWindowTitle(QApplication::translate("Hedit", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class Hedit: public Ui_Hedit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HEDIT_H
