#include "health.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>

Health::Health(){}

void Health::setHealthBar(int x, int y)
{
    baseRect->setRect(x, y, maxHealth/10, 20); //drawing base rectangle
    QPen blackPen(Qt::black);
    blackPen.setWidth(3);
    QBrush grayBrush(Qt::gray);
    baseRect->setPen(blackPen);
    baseRect->setBrush(grayBrush);
    scene()->addItem(baseRect);

    rect2->setRect(x, y, maxHealth/10, 20); //drawing second rectangle
    QBrush greenBrush(Qt::green);
    rect2->setBrush(greenBrush);
    scene()->addItem(rect2);
}

void Health::updateHealthBar() //called when health changes
{
    rect2->setRect(rect2->x(), rect2->y(), health/10, 20); //updates size of the health bar
    QBrush greenBrush(Qt::green);
    QBrush redBrush(Qt::red);
    QBrush yellowBrush(Qt::darkYellow);
    if (health <= maxHealth/4) //red if health is too low
        rect2->setBrush(redBrush);
    else
        if (health <= maxHealth/2) //dark yellow if health is less than half
            rect2->setBrush(yellowBrush);
        else
            rect2->setBrush(greenBrush); //green if health is more than half

    scene()->addItem(rect2);

}


int Health::getHealth()
{
    return health;
}


int Health::getMaxHealth()
{
    return maxHealth;
}

void Health::setHealth(int number)
{
    health = number;
}

void Health::setMaxHealth(int number)
{
    maxHealth = number;
}

void Health::decrementHealth()
{
    health--;
    this->updateHealthBar();

}

void Health::incrementHealth()
{
    health++;
    this->updateHealthBar();
}
