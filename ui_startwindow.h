/********************************************************************************
** Form generated from reading UI file 'startwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTWINDOW_H
#define UI_STARTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QProgressBar>

QT_BEGIN_NAMESPACE

class Ui_startwindow
{
public:
    QProgressBar *progressBar;

    void setupUi(QDialog *startwindow)
    {
        if (startwindow->objectName().isEmpty())
            startwindow->setObjectName("startwindow");
        startwindow->resize(400, 300);
        progressBar = new QProgressBar(startwindow);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(90, 160, 221, 20));
        progressBar->setValue(24);

        retranslateUi(startwindow);

        QMetaObject::connectSlotsByName(startwindow);
    } // setupUi

    void retranslateUi(QDialog *startwindow)
    {
        startwindow->setWindowTitle(QCoreApplication::translate("startwindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class startwindow: public Ui_startwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTWINDOW_H
