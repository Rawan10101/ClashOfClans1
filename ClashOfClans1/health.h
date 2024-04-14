#ifndef HEALTH_H
#define HEALTH_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsItem>

class Health: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Health();

    void setHealthBar(int x, int y);
    int getHealth();
    int getMaxHealth();
    void setHealth(int);
    void setMaxHealth(int);
    void decrementHealth();
    void incrementHealth();

private:
    int health;
    int maxHealth;
    QGraphicsRectItem * baseRect = new QGraphicsRectItem;
    QGraphicsRectItem* rect2 = new QGraphicsRectItem;
    void updateHealthBar(); //private bcuz it is only called by member functions
};

#endif // HEALTH_H
