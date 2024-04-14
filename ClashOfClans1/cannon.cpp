#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QDialog>
#include "cannon.h"
#include "bullet.h"
#include "health.h"
#include <QGraphicsRectItem>

Cannon::Cannon(QPixmap pixmap)
{
    health->setMaxHealth(10); //set the max health of the cannon
    health->setHealthBar(this->x(), this->y());

    // QPixmap pixmap(":/images/Cannon.png");
    this->setPixmap(pixmap);
}

void Cannon::upgrade() //function is called when user chooses to upgrade and they have enough money
{
    health->setMaxHealth(health->getMaxHealth()*1.5); //increase max health by 1.5 every upgrade
    health->setHealth(health->getMaxHealth()); //sets health back to max health
}

void Cannon::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton)
    {
        bullet = new Bullet();
        bullet->setDirection(event->position().x(), event->position().y());
        bullet->setPos(x(),y()); //sets position of the bullet at the position of the cannon
        scene()->addItem(bullet);
    }

}

// void Cannon::paintEvent(QPaintEvent *event) //to display cannon's health bar
// {
//     QDialog::paintEvent(event);

//     QPainter painter(this);
//     painter.setRenderHint(QPainter::Antialiasing);
//     painter.setBrush(Qt::gray);
//     painter.setPen(Qt::black);
//     painter.drawRect(rect());

//     qreal width = rect().width() * health->getHealth() / 100.0;
//     QRectF healthBarRect(rect().topLeft(), QSizeF(width, 10));
//     painter.setBrush(Qt::green);
//     painter.setPen(Qt::NoPen);
//     painter.drawRect(healthBarRect);
// }

void Cannon::cannonAttacked() //to handle collision with enemy
{

    health->decrementHealth();
    if (health->getHealth() <= 0) //cannon is destroyed
    {
        delete this;
        //update health bar
        //message
        //sound

    }
}

//Notes:
//bullet movement handled in bullet class
//add the code to direct the cannon towards the firing location
//fix the paintEvent function
//figure out how much the health decreases every attack and handle it in the cannonAttacked function
//when cannon gets destroyed, display message to inform user that cannon has been destroyed
//add sound when cannon is destroyed









/*OLD CODE*/
// #include "cannon.h"

// Cannon::Cannon(QWidget *parent, QGraphicsScene* scene)
//     : QDialog(parent),
//       ui(new Ui::Cannon),
//       scene(scene),
//       health(new Health()),
//       bullet(nullptr),
//       bulletTimer(new QTimer(this)),
//       bulletDirectionX(0),
//       bulletDirectionY(0),
//       bulletFired(false),
//       bulletMoving(false)
// {
//     ui->setupUi(this);
//     setFocusPolicy(Qt::StrongFocus);

//     // Connect the bullet timer signal to the moveBullet slot
//     connect(bulletTimer, SIGNAL(timeout()), this, SLOT(moveBullet()));
// }

// Cannon::~Cannon()
// {
//     delete ui;
//     delete health;
//     delete bullet;
//     delete bulletTimer;
// }

// void Cannon::decreaseHealth()
// {
//     health->reduceHealth();

//     if (health->getHealth() <= 0)
//     {
//         // Cannon destroyed logic
//     }
// }

// void Cannon::upgrade()
// {
//     // Upgrade cannon logic
// }

// void Cannon::setBulletDirection(int x, int y)
// {
//     bulletDirectionX = x;
//     bulletDirectionY = y;
// }

// void Cannon::shootBullet()
// {
//     if (!bulletFired && !bulletMoving)
//     {
//         bullet = new Bullet();
//         bullet->setPos(x() + width() / 2, y());
//         bullet->setDirection(bulletDirectionX, bulletDirectionY);
//         scene->addItem(bullet);

//         bulletMoving = true;
//         bulletFired = true;

//         bulletTimer->start(10);
//     }
// }

// void Cannon::paintEvent(QPaintEvent *event)
// {
//     QDialog::paintEvent(event);

//     QPainter painter(this);
//     painter.setRenderHint(QPainter::Antialiasing);
//     painter.setBrush(Qt::gray);
//     painter.setPen(Qt::black);
//     painter.drawRect(rect());

//     qreal width = rect().width() * health->getHealth() / 100.0;
//     QRectF healthBarRect(rect().topLeft(), QSizeF(width, 10));
//     painter.setBrush(Qt::green);
//     painter.setPen(Qt::NoPen);
//     painter.drawRect(healthBarRect);
// }

// void Cannon::keyPressEvent(QKeyEvent *event)
// {
//     if (event->key() == Qt::Key_Left)
//     {
//         bulletDirectionX = -1;
//     }
//     else if (event->key() == Qt::Key_Right)
//     {
//         bulletDirectionX = 1;
//     }
//     else if (event->key() == Qt::Key_Up)
//     {
//         bulletDirectionY = -1;
//     }
//     else if (event->key() == Qt::Key_Down)
//     {
//         bulletDirectionY = 1;
//     }
//     else if (event->key() == Qt::Key_Space)
//     {
//         shootBullet();
//     }

//     event->accept();
// }

// void Cannon::keyReleaseEvent(QKeyEvent *event)
// {
//     if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
//     {
//         bulletDirectionX = 0;
//     }
//     else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down)
//     {
//         bulletDirectionY = 0;
//     }

//     event->accept();
// }

// void Cannon::moveBullet()
// {
//     if (bulletMoving)
//     {
//         bullet->move();

//         if (bullet->collidesWithEnemy())
//         {
//             // Bullet hit an enemy logic
//             bulletMoving = false;
//             bulletTimer->stop();
//             delete bullet;
//         }
//         else if (bullet->x() < 0 || bullet->x() > 800 || bullet->y() < 0 || bullet->y() > 800)
//         {
//             // Bullet reached the end of the screen logic
//             bulletMoving = false;
//             bulletTimer->stop();
//             delete bullet;
//         }
//     }
// }
