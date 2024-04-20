#include "townhall.h"

Townhall::Townhall(QPixmap pixmap)
{
    health->setMaxHealth(10); //adjust max health later
    this->setPixmap(pixmap); //pixmap is sent from game.cpp
    health->setHealthBar(this->x(), this->y());
    destroyed = 0; //bool variable to indicate if townhall got destroyed
}

void Townhall::upgrade() //function is called when user chooses to upgrade and they have enough money
{
    health->setMaxHealth(health->getMaxHealth()*1.5); //increase max health by 1.5 every upgrade
    health->setHealth(health->getMaxHealth()); //sets health back to max health
}

void Townhall::townhallAttacked() //to handle collision with enemy
{
    health->decrementHealth();
    if (health->getHealth() <= 0) // is destroyed
    {
        bool collisionStartTime;
        collisionStartTime = QDateTime::currentDateTime().toTime_t();
        if (QDateTime::currentDateTime().toTime_t() - collisionStartTime >= 30)
        {
            health->decrementHealth();
        }
        else if (collidingWithCastle)
        {
            collidingWithObject = false;

        }
        destroyed = 1;
        //delete this;
        //update health bar
        //message
        //sound
}

bool Townhall::getStatus()
{
    return destroyed;
}


/*Notes:*/
//Add health bar
//adjust max health
//when destroyed=1, game is over



/*OLD CODE*/
// #include "townhall.h"

// TownHall::TownHall(QWidget *parent)
//     : QDialog(parent),
//     health(new Health())
// {

//     this->setPixmap(pixmap);
//     setFlag(QGraphicsItem::ItemIsFocusable);
// }

// TownHall::~TownHall()
// {
//     delete ui;
//     delete health;
// }

// void TownHall::reduceHealth()
// {
//     health->decrementHealth();

//     if (health->getHealth() <= 0)
//     {
//         delete this;
//     }
// }

// void TownHall::upgrade()
// {

// }

// QRectF TownHall::boundingRect() const
// {
//     return QRectF(0, 0, 100, 100);
// }

// void TownHall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
// {
//     Q_UNUSED(option);
//     Q_UNUSED(widget);

//     painter->setBrush(Qt::blue);
//     painter->drawEllipse(boundingRect());
// }

// void TownHall::move()
// {
//     QList<QGraphicsItem*> collidingItemsList = collidingItems();
//     for (int i = 0; i < collidingItemsList.size(); i++)
//     {
//         if (typeid(*(collidingItemsList[i])) == typeid(TownHall) && health->getHealth() > 0)
//         {
//             reduceHealth();

//             delete collidingItemsList[i];
//             return;
//         }
//     }
// }
