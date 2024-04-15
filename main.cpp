#include "Game.h"

#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game w;
    //  QString filePath = QCoreApplication::applicationDirPath() + "file:///C:/Users/HP/Desktop/file1/File.txt";
    //  w.loadClanDesignFromFile(filePath);
    // w.printClanDesign();
   w.displayClanDesign();
    w.show();

    return a.exec();
}



