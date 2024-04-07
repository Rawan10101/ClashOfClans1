#ifndef CANNON_H
#define CANNON_H

#include <QDialog>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>
#include <QPainter>
#include "ui_cannon.h"
#include "health.h"
#include "bullet.h"

class Cannon : public QDialog
{
    Q_OBJECT

public:
    explicit Cannon(QWidget *parent = nullptr, QGraphicsScene* scene = nullptr);
    ~Cannon();

    void decreaseHealth();
    void upgrade();
    void setBulletDirection(int x, int y);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void shootBullet();
    void moveBullet();

private:
    Ui::Cannon *ui;
    QGraphicsScene* scene;
    Health* health;
    Bullet* bullet;
    QTimer* bulletTimer;
    int bulletDirectionX;
    int bulletDirectionY;
    bool bulletFired;
    bool bulletMoving;
};

#endif // CANNON_H
