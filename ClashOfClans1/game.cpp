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
    layout->addWidget(view);

    QPixmap backgroundPixmap(":/images/Background.png"); //Set the background image
    if (!backgroundPixmap.isNull())
    {
        QGraphicsPixmapItem* backgroundItem = new QGraphicsPixmapItem(backgroundPixmap);
        scene->addItem(backgroundItem); // Add the background to the scene
        sceneWidth = backgroundPixmap.width(); // Set the scene width equal to the background image width
        sceneHeight = backgroundPixmap.height(); // Set the scene height == the background image height
    }

    clanDesign.clear(); //clan design vector

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
    adjustSceneSize(); // Function at the end will adjust the size of the scene but based on the loaded clan design
}



void Game::displayClanDesign()
{
    const int fenceSize = 200;
    const int castleSize = 80;
    const int cannonSize = 60;
    for (int i = 0; i < clanDesign.size(); i++)
    {
        for (int j = 0; j < clanDesign[i].size(); j++)
        {
            int element = clanDesign[i][j]; // Get the element at the current position

            QPixmap pixmap;

            switch (element)
            {
            case 0:
                // Use an empty pixmap for case 0
                pixmap = QPixmap();
                break;
            case 1: //castle
            {
                pixmap.load(":/images/Castle.png");
                pixmap = scalePixmap(pixmap, castleSize, castleSize);
                Townhall* townhall = new Townhall(pixmap);
                townhall->setPos(j * cellSize , i * cellSize);
                scene->addItem(townhall);

            }
            break;
            case 2: //cannon
            {
                pixmap.load(":/images/Cannon.png");
                pixmap = scalePixmap(pixmap, cannonSize, cannonSize);
                Cannon* cannon = new Cannon(pixmap);
                cannon->setPos(j * cellSize , i * cellSize);
                scene->addItem(cannon);
            }
            break;
            case 3: //fence
            {
                pixmap.load(":/images/Wall.png");
                pixmap = scalePixmap(pixmap, fenceSize, fenceSize);
                Fence* fence = new Fence(pixmap);
                fence->setPos(j * cellSize , i * cellSize);
                scene->addItem(fence);

            }
            break;
            default:
                break;
            }

            // if (!pixmap.isNull())
            // {
            //     QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap); // Create a pixmap with the current pixmap
            //     item->setPos(j * cellSize , i * cellSize);   // Set the position of the pixmap item
            //     scene->addItem(item); // Add the pixmap to the scene
            // }
        }
    }
}


QPixmap Game::scalePixmap(const QPixmap& pixmap, int width, int height) // Scale a pixmap to fit the scene and our dimensions
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
