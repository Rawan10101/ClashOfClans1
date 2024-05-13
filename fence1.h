#ifndef FENCE1_H
#define FENCE1_H

#include <QDialog>

#include <QGraphicsItem>
#include <QPainter>
#include <QPushButton>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QObject>
#include "health.h"

class Fence1 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:

    bool markedForRemoval() const { return remove; }
    void markForRemoval() { remove = true; }
    static qreal healthValue;

    Fence1(QString type);
    ~Fence1();
    bool remove;
    Health* fenceHealth;
    QString fenceType; //horizontal or vertical
    bool underRepair;
    bool destroyed = false;
    void UpgradeButton();
    void setPix(QPixmap image);

private:
    QPixmap fenceImage;
    QPixmap upgradedFenceImage;
    int upgradeCost;
signals:
    void fenceUpgraded(const QPixmap& newImage, int newHealth);

};

#endif // FENCE1_H
