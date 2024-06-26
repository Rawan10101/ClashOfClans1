#ifndef FENCE_H
#define FENCE_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QImage>
#include <QPainter>
#include <QPushButton>


#include "health.h"

class Fence : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    // Fence(QObject *parent = nullptr);
    Fence(QPixmap pixmap);
    void decreaseHealth();
    void upgrade();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

public slots:
    void collide();
    void onUpgradeButtonClicked();

private:
    Health* health;
    QImage fenceImage;
    QImage upgradedFenceImage;
    QPushButton* upgradeButton;
    int collisionCount;
    int collisionTimerCount;
    int upgradeCost;
};

#endif // FENCE_H
