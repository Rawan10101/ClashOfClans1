/********************************************************************************
** Form generated from reading UI file 'shop1.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOP1_H
#define UI_SHOP1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Shop1
{
public:
    QPushButton *townHall;
    QPushButton *fence;
    QPushButton *cannon;
    QPushButton *town;
    QPushButton *fencebutton;
    QPushButton *cannonbutton;

    void setupUi(QDialog *Shop1)
    {
        if (Shop1->objectName().isEmpty())
            Shop1->setObjectName("Shop1");
        Shop1->resize(407, 262);
        townHall = new QPushButton(Shop1);
        townHall->setObjectName("townHall");
        townHall->setGeometry(QRect(30, 150, 75, 24));
        fence = new QPushButton(Shop1);
        fence->setObjectName("fence");
        fence->setGeometry(QRect(160, 150, 75, 24));
        cannon = new QPushButton(Shop1);
        cannon->setObjectName("cannon");
        cannon->setGeometry(QRect(290, 150, 75, 24));
        town = new QPushButton(Shop1);
        town->setObjectName("town");
        town->setGeometry(QRect(20, 60, 101, 61));
        fencebutton = new QPushButton(Shop1);
        fencebutton->setObjectName("fencebutton");
        fencebutton->setGeometry(QRect(150, 60, 91, 61));
        cannonbutton = new QPushButton(Shop1);
        cannonbutton->setObjectName("cannonbutton");
        cannonbutton->setGeometry(QRect(280, 60, 91, 61));

        retranslateUi(Shop1);

        QMetaObject::connectSlotsByName(Shop1);
    } // setupUi

    void retranslateUi(QDialog *Shop1)
    {
        Shop1->setWindowTitle(QCoreApplication::translate("Shop1", "Dialog", nullptr));
        townHall->setText(QCoreApplication::translate("Shop1", "Upgrade", nullptr));
        fence->setText(QCoreApplication::translate("Shop1", "Upgrade", nullptr));
        cannon->setText(QCoreApplication::translate("Shop1", "Upgarde", nullptr));
        town->setText(QString());
        fencebutton->setText(QString());
        cannonbutton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Shop1: public Ui_Shop1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOP1_H
