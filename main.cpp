#include <QApplication>
#include "startgame.h"
#include "game.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    StartGame x;
    x.show();

    Game w;
    w.loadClanDesignFromFile("C:/Users/HP/Desktop/New Text Document.txt");
    w.printClanDesign();
    w.displayClanDesign();


    w.setScene(x.scene);


    w.show();

    return a.exec();
}
