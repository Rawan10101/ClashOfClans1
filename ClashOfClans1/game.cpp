#include "Game.h"
#include "cannon.h"
#include "fence.h"
#include "townhall.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QFrame>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

Game::Game(QWidget *parent) : QWidget(parent)
{
    QFile file(":/File.txt"); // Open the file
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(this, "Error", "Failed to open file: File.txt");
        return;
    }

    layout = new QGridLayout(this);
    setLayout(layout);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene);
    view->setStyleSheet("background: transparent; border: 0px");
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    layout->addWidget(view);

    QPixmap backgroundPixmap(":/images/Background.png"); // Set the background image
    if (!backgroundPixmap.isNull())
    {
        view->setBackgroundBrush(backgroundPixmap); // Set the background image as the view's background brush
        sceneWidth = backgroundPixmap.width(); // Set the scene width equal to the background image width
        sceneHeight = backgroundPixmap.height(); // Set the scene height equal to the background image height
    }

    clanDesign.clear(); // Clear the clan design vector

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine(); // Read a line from the file
        QStringList values = line.split(',');

        QVector<int> row;
        for (const QString& value : values)
        {
            bool ok;
            int element = value.toInt(&ok); // Convert the value to an int
            if (ok)
                row.append(element);
            else
                row.append(0);
        }
        clanDesign.append(row);
    }

    file.close();
    //adjustSceneSize(); // Adjust the size of the scene based on the loaded clan design
    displayClanDesign(); // Display the clan design on the scene
    qDebug() << clanDesign[0][1] << "test";
    scene->setSceneRect(0,0,clanDesign.size()*50,clanDesign[0].size()*50);
    view->resize(clanDesign.size()*50,clanDesign[0].size()*50);
}

void Game::displayClanDesign()
{
    const int fenceSize = 50;
    const int castleSize = 50;
    const int cannonSize = 50;


    //error here
    for (int i = 0; i < clanDesign.size(); i++)
    {
        for (int j = 0; j < clanDesign[i].size(); j++)
        {
            int element = clanDesign[i][j]; // Get the element at the current position

            if(element == 0)
            {
                // Use an empty pixmap for case 0
                //break; //removing break causes a crash
            }
            else if(element == 1) // castle
            {
                QPixmap piTest(":/images/Castle.png");
                piTest = piTest.scaled(50,50);
                Townhall* townhall = new Townhall(piTest);
                townhall->setPos(j * castleSize, i * castleSize);
               // townhall->setPos(50,50);
                scene->addItem(townhall);
            }
            else if(element == 2) // cannon
            {
                //pixmap.load(":/images/Cannon.png");
                //pixmap = scalePixmap(pixmap, cannonSize, cannonSize);
                //Cannon* cannon = new Cannon(pixmap);
                //cannon->setPos(j * cellSize, i * cellSize);
                //scene->addItem(cannon);
            }
            else if(element == 3) // fence
            {
                //pixmap.load(":/images/Wall.png");
                //pixmap = scalePixmap(pixmap, fenceSize, fenceSize);
                //Fence* fence = new Fence(pixmap);
                //fence->setPos(j * cellSize, i * cellSize);
                //scene->addItem(fence);
            }

     //       if (!pixmap.isNull())
       //     {
         //       QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap); // Create a pixmap with the current pixmap
           //     item->setPos(j * cellSize, i * cellSize);   // Set the position of the pixmap item
              //  scene->addItem(item); // Add the pixmap to the scene
           // }
        }
    }
}

QPixmap Game::scalePixmap(const QPixmap& pixmap, int width, int height)
{
    if (pixmap.width() <= width && pixmap.height() <= height)
    {
        // No need to scale the pixmap if it fits within the desired dimensions
        return pixmap;
    }

    return pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation); // Scale the pixmap while maintaining aspect ratio
}

void Game::adjustSceneSize() {
    const int x = 0;

    if (sceneWidth > 0 && sceneHeight > 0)
    {
        int widgetWidth = view->width();
        int widgetHeight = view->height();

        // Adjust the size of the scene to fit the widget
        qreal scale = qMin((widgetWidth - x) / qreal(sceneWidth),
  (widgetHeight - x) / qreal(sceneHeight));
        int newSceneWidth = int(sceneWidth * scale); //  the scene width
        int newSceneHeight = int(sceneHeight * scale); // the scene height

        // Set the background to cover the whole scene
        QPixmap backgroundPixmap(":/images/Background.png");
        if (!backgroundPixmap.isNull())
        {
            QPixmap scaledBackgroundPixmap = backgroundPixmap.scaled(newSceneWidth, newSceneHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation); // Scale the background pixmap to fit the new scene dimensions
            scene->setBackgroundBrush(scaledBackgroundPixmap); // Set the background as the background for the scene
        }

        // Adjust the cell size based on the new scene size
        cellSize = qMin(newSceneWidth / clanDesign[0].size(),
                        newSceneHeight / clanDesign.size()); // Calculate the new cell size based on the scene dimensions and clan design
    }
}

/*void Game::printClanDesign() // print the clan design
{
    for (const QVector<int>& row : clanDesign)
    {
       for (int element : row)
        {
            qDebug() << element << " "; // Print the element
        }
        qDebug() << "\n"; // Print a newline between rows
    }
}
*/
