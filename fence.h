#ifndef FENCE_H
#define FENCE_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QImage>
#include <QPainter>
#include <QPushButton>

#include "health.h"

class Fence : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Fence(QObject *parent = nullptr);

    void decreaseHealth();
    void upgrade();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

public slots:
    void move();
    void onUpgradeButtonClicked();

private:
    Health* health;
    QImage fenceImage;
    QPushButton* upgradeButton;
    int collisionCount;
    int collisionTimerCount;
};

#endif // FENCE_H
