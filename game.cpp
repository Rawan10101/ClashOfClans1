#include "game.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QGraphicsScene>

Game::Game(QWidget *parent) : QGraphicsView(parent)
{
    //Scene, Money, Elixir
    scene = new QGraphicsScene(this);
    setScene(scene);

    const int sceneWidth = 800;
    const int sceneHeight = 600;
    scene->setSceneRect(0, 0, sceneWidth, sceneHeight);

    setting = new QPushButton("Settings", this);
    setting->setFixedSize(100, 30);

    money = new QProgressBar(this);
    elixir = new QProgressBar(this);
    money->setRange(0, 100);
    elixir->setRange(0, 100);

    QHBoxLayout* topLayout = new QHBoxLayout;
    topLayout->addWidget(setting);
    topLayout->addStretch();
    topLayout->addWidget(new QLabel("Money:"));
    topLayout->addWidget(money);
    topLayout->addWidget(new QLabel("Elixir:"));
    topLayout->addWidget(elixir);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(this);

    QWidget* widget = new QWidget(this);
    widget->setLayout(mainLayout);
    setViewport(widget);
}

void Game::loadClanDesignFromFile(const QString& filePath)
{
    // Read File
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file: " << filePath;
        return;
    }

    clanDesign.clear();

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList values = line.split(',');

        QVector<int> row;
        for (const QString& value : values)
        {
            bool ok;
            int element = value.toInt(&ok);
            if (ok)
                row.append(element);
            else
                row.append(0);
        }

        clanDesign.append(row);
    }

    file.close();
}

void Game::printClanDesign()
{
    for (const QVector<int>& row : clanDesign)
    {
        for (int element : row)
        {
            qDebug() << element << " ";
        }
        qDebug() << "\n";
    }
}

void Game::displayClanDesign()
{
    const int cellSize = 50;

    for (int i = 0; i < clanDesign.size(); i++)
    {
        for (int j = 0; j < clanDesign[i].size(); j++)
        {
            int element = clanDesign[i][j];

            QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem();

            switch (element)
            {
            case 0:
                pixmapItem->setPixmap(QPixmap("C:/Users/HP/Downloads/thumb.jpg"));
                break;
            case 1:
                pixmapItem->setPixmap(QPixmap("C:/Users/HP/Downloads/Clan_Castle11.webp"));
                break;
            case 2:
                pixmapItem->setPixmap(QPixmap("C:/Users/HP/Downloads/Cannon21G.webp"));
                break;
            case 3:
                pixmapItem->setPixmap(QPixmap(":/images/fence.png"));
                break;
            default:
                break;
            }

            QPixmap scaledPixmap = pixmapItem->pixmap().scaled(cellSize, cellSize, Qt::KeepAspectRatio);
            pixmapItem->setPixmap(scaledPixmap);
            pixmapItem->setPos(j * cellSize, i * cellSize);

            scene->addItem(pixmapItem);
        }
    }
}
