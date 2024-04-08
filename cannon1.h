#ifndef CANNON1_H
#define CANNON1_H
#include <QMouseEvent>
#include "health.h"
#include "bullet.h"

class Cannon1 : public QObject
{
    Q_OBJECT

public:
    Cannon1();
    //void decreaseHealth();
    void upgrade();
    void mousePressEvent(QMouseEvent *event); //to release bullet on click
    //function for direction of bullet
    void shootBullet();
    void paintEvent(QPaintEvent* event); //for health bar

private:
    Health* health = new Health;
    Bullet* bullet;

};

#endif // CANNON1_H
