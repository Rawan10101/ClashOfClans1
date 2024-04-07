#include "townhall.h"

TownHall::TownHall(QWidget *parent)
    : QDialog(parent),
    health(new Health())
{

    setFlag(QGraphicsItem::ItemIsFocusable);
}

TownHall::~TownHall()
{
    delete ui;
    delete health;
}

void TownHall::reduceHealth()
{
    health->reduceHealth();

    if (health->getHealth() <= 0)
    {
        delete this;
    }
}

void TownHall::upgrade()
{

}

QRectF TownHall::boundingRect() const
{
    return QRectF(0, 0, 100, 100);
}

void TownHall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::blue);
    painter->drawEllipse(boundingRect());
}

void TownHall::move()
{
    QList<QGraphicsItem*> collidingItemsList = collidingItems();
    for (int i = 0; i < collidingItemsList.size(); i++)
    {
        if (typeid(*(collidingItemsList[i])) == typeid(TownHall) && health->getHealth() > 0)
        {
            reduceHealth();

            delete collidingItemsList[i];
            return;
        }
    }
}
