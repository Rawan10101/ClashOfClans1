#include "fence1.h"
#include "troop.h"
#include <QTimer>
#include <QList>
#include <QDebug>
#include <QPixmap>
#include<QObject>
#include<QGraphicsScene>
// #include<game.h>
Fence1::Fence1(QString type)
{
    QPixmap pixmap(":/images/Wall.png");
    pixmap = pixmap.scaledToWidth(50);
    pixmap = pixmap.scaledToHeight(50);
    this->setPixmap(pixmap);
    fenceHealth = new Health(healthValue);
    fenceType = type;
    remove=false;

    // setFlag(QGraphicsItem::ItemIsSelectable, true);
}

qreal Fence1::healthValue = 1000;

Fence1::~Fence1()
{
}

void Fence1::UpgradeButton()
{
    QPixmap pixmap(":/images/Castle.png");
    // QPixmap newImage("C:/Users/HP/Downloads/Wall3.webp");
    pixmap = pixmap.scaledToWidth(50);
    pixmap = pixmap.scaledToHeight(50);
    this->setPixmap(pixmap);
    fenceHealth->setMaxHealth(15);
    // int newHealth = 15;
    // fenceHealth->setMaxHealth(newHealth);

    // emit fenceUpgraded(newImage, newHealth);
}
void Fence1::setPix(QPixmap image){
    this->setPixmap(image);
}
