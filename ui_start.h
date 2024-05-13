/********************************************************************************
** Form generated from reading UI file 'start.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_START_H
#define UI_START_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Start
{
public:
    QPushButton *start;
    QPushButton *sound;
    QPushButton *howtoplay;
    QPushButton *Quit;

    void setupUi(QDialog *Start)
    {
        if (Start->objectName().isEmpty())
            Start->setObjectName("Start");
        Start->resize(364, 300);
        start = new QPushButton(Start);
        start->setObjectName("start");
        start->setGeometry(QRect(140, 120, 75, 24));
        sound = new QPushButton(Start);
        sound->setObjectName("sound");
        sound->setGeometry(QRect(140, 190, 91, 24));
        howtoplay = new QPushButton(Start);
        howtoplay->setObjectName("howtoplay");
        howtoplay->setGeometry(QRect(140, 150, 81, 24));
        Quit = new QPushButton(Start);
        Quit->setObjectName("Quit");
        Quit->setGeometry(QRect(140, 220, 75, 20));

        retranslateUi(Start);

        QMetaObject::connectSlotsByName(Start);
    } // setupUi

    void retranslateUi(QDialog *Start)
    {
        Start->setWindowTitle(QCoreApplication::translate("Start", "Dialog", nullptr));
        start->setText(QCoreApplication::translate("Start", "Start", nullptr));
        sound->setText(QCoreApplication::translate("Start", "Sound Setting", nullptr));
        howtoplay->setText(QCoreApplication::translate("Start", "How to play?", nullptr));
        Quit->setText(QCoreApplication::translate("Start", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Start: public Ui_Start {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_H
