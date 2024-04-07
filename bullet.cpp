#include "bullet.h"

Bullet::Bullet()
    : directionX(0),
    directionY(0),
    speed(5.0)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
}

void Bullet::setDirection(int x, int y)
{
    directionX = x;
    directionY = y;
}

void Bullet::move()
{
    qreal dx = directionX * speed;
    qreal dy = directionY * speed;
    setPos(mapToParent(dx, dy));
}

bool Bullet::collidesWithEnemy()
{
    return false;
}

QRectF Bullet::boundingRect() const
{
    return QRectF(-5, -5, 10, 10);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::red);
    painter->drawEllipse(boundingRect());
}
