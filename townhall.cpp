#include "townhall.h"
#include <QDebug>
Townhall::Townhall( )
{


    // QPixmap pixmap(":/images/Castle.png");
    QPixmap pixmap(":/images/cake1.png");
    pixmap = pixmap.scaledToWidth(50);
    pixmap = pixmap.scaledToHeight(50);
    this->setPixmap(pixmap);
    townhallHealth = new Health(healthValue);
    qDebug() << "testing townhall";

    remove=false;

}

qreal Townhall::healthValue = 1000;

void Townhall::UpgradeButton()
{
    // QPixmap pixmap(":/images/Castle.png");
    // pixmap = pixmap.scaledToWidth(50);
    // pixmap = pixmap.scaledToHeight(50);
    // this->setPixmap(pixmap);
    // townhallHealth->setMaxHealth(15);
}

void Townhall::setPix1(QPixmap image){
    this->setPixmap(image);
}







// int Townhall::reduceHealth(){
//     return (health->getHealth())-1;
// }
// void Townhall::upgrade() //function is called when user chooses to upgrade and they have enough money
// {
//     health->setMaxHealth(health->getMaxHealth()*1.5); //increase max health by 1.5 every upgrade
// }

// void Townhall::townhallAttacked() //to handle collision with enemy
// {
//     health->decrementHealth();
//     if (health->getHealth() <= 0) // is destroyed
//     {
//         destroyed = 1;
//         //delete this;
//         //update health bar
//         //message
//         //sound

//     }
// }

// bool Townhall::getStatus()
// {
//     return destroyed;
// }



