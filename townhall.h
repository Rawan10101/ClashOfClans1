#ifndef TOWNHALL_H
#define TOWNHALL_H

#include <QDialog>
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QImage>
#include "health.h"

namespace Ui {
class TownHall;
}

class TownHall : public QDialog, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit TownHall(QWidget *parent = nullptr);
    ~TownHall();

    void reduceHealth();
    void move();
    void upgrade();

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    Ui::TownHall *ui;
    Health *health;
};

#endif // TOWNHALL_H
