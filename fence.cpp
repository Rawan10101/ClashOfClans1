
#include "fence.h"
#include "troop.h"
#include <QTimer>
#include <QList>
#include <QDebug>
#include "globalvariables.h"
#include <QPixmap>
#include<QObject>
#include<QGraphicsScene>
#include <globalvariables.h>

Fence::Fence(QPixmap pixmap)
    : collisionCount(0), collisionTimerCount(0), upgradeCost(20)
{
    health = new Health(nullptr, 0, 0, 10); // Pass the correct parameters here
    this->setPixmap(pixmap);
    health->setMaxHealth(10); // adjust max health later
    health->updateHealthBar();



     fenceImage.load(":/images/fence.png");
     upgradedFenceImage.load(":/images/upgraded_fence.png");

   upgradeButton = new QPushButton("Upgrade", nullptr);
    upgradeButton->setFixedSize(80, 30);
    upgradeButton->setVisible(false);

   //connect(upgradeButton, &QPushButton::clicked, this, &Fence::onUpgradeButtonClicked);

    //QTimer* timer = new QTimer(this);
  //connect(timer, SIGNAL(timeout()), this, SLOT(move()));
   // timer->start(50);
}
void Fence::setPixmap(const QPixmap& pixmap) {
 // QGraphicsPixmapItem::setPixmap(pixmap);
}
 void Fence::decreaseHealth()
 {
     health->decrementHealth();

     if (health->getHealth() <= 0)
     {
         delete this;
     }
 }

 void Fence::upgrade()
 {
     if (upgradeCost <= 20) {  // Assuming playerMoney is a variable that holds the player's available money
         health->setMaxHealth(health->getMaxHealth()*1.5); //increase max health by 1.5 every upgrade
         health->setHealth(health->getMaxHealth()); //sets health back to max health
         fenceImage = upgradedFenceImage;
         upgradeButton->setVisible(false);
         qDebug() << "Fence upgraded!";
     } else {
         qDebug() << "Insufficient funds to upgrade the fence!";
     }
 }

 void Fence::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
 {
     painter->drawImage(boundingRect(), fenceImage);

     qreal width = boundingRect().width() * health->getHealth() / health->getMaxHealth();
     QRectF healthBarRect(boundingRect().topLeft(), QSizeF(width, 5));
     painter->fillRect(healthBarRect, Qt::green);
 }

 void Fence::collide()
 {
     QList<QGraphicsItem*> collidingItemsList = collidingItems();
     for (int i = 0; i < collidingItemsList.size(); i++)
     {
         if (typeid(*(collidingItemsList[i])) == typeid(Troop) && health->getHealth() > 0)
         {
             collisionCount++;
             collisionTimerCount++;

             if (collisionCount >= 10 )
             {
                 decreaseHealth();
                 collisionCount = 0;
                 collisionTimerCount = 0;
             }


             if (health->getHealth() <= 0)
             {
                upgradeButton->setVisible(false);
             }
             else
             {
                 upgradeButton->setVisible(true);
}

             return;
         }
     }
    //  Reset the collision count if no collisions occur within 10 seconds
              if (collisionTimerCount >= 10)
     {
        collisionCount = 0;
         collisionTimerCount = 0;
     }
 }

 void Fence::onUpgradeButtonClicked()
 {
    upgrade();
 }

