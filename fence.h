#ifndef FENCE_H
#define FENCE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPushButton>
#include "health.h"
#include <QPixmap>
class Fence : public QGraphicsItem
{
public:
    Fence(QPixmap pixmap);
    void setPixmap(const QPixmap& pixmap);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override { return QRectF(0, 0, 100, 100); }
    void decreaseHealth();
    void upgrade();
    void collide();
    void onUpgradeButtonClicked();

private:
    Health* health;
    int collisionCount;
    int collisionTimerCount;
    int upgradeCost;
    QImage fenceImage;
    QImage upgradedFenceImage;
    QPushButton* upgradeButton;
};

#endif // FENCE_H
