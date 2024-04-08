#include <QMouseEvent>
#include <QGraphicsScene>
#include "cannon1.h"
#include "bullet.h"
#include "health.h"

Cannon1::Cannon1()
{
    health->setMaxHealth(10);
}

void Cannon1::upgrade()
{
    health->setMaxHealth(health->getMaxHealth()*1.5);
    health->setHealth(health->getMaxHealth());
}

void Cannon1::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton)
    {
        bullet = new Bullet();
        bullet->setPos(x() + width() / 2, y());
        // Bullet->setDirection(bulletDirectionX, bulletDirectionY);
        scene->addItem(bullet);


    }

}

void Cannon1::shootBullet()
{

}






