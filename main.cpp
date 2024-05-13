#include "Game.h"
#include "startwindow.h"
#include "shop1.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Game w;
    startwindow w;

    w.show();

    return a.exec();
}



