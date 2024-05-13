#include "workers.h"
#include "troop.h"
#include "game.h"
#include <QRandomGenerator>
#include <QGraphicsItem>



Workers::Workers() : targetFence(nullptr)
{
    QPixmap workerImage(":/images/citizenworker.png");
    setPixmap(workerImage.scaled(30, 30));

    workerTimer = new QTimer();
    connect(workerTimer,SIGNAL(timeout()),this,SLOT (move()));
    // isDestroyed = false;

    danceTimer = new QTimer;
    connect(danceTimer, SIGNAL(timeout()), this, SLOT(dance()));
    dTimer = new QTimer;
    connect(dTimer, SIGNAL(timeout()), this, SLOT(danceUtil()));
    dTimer->start(300);

}

void Workers::setFence(Fence1* fence)
{
    targetFence = fence;
}

void Workers::dance()
{
    dancing = true;
    danceTimer->start(300);
    setPos(x(), y()-15);

}

void Workers::danceUtil()
{
    if (dancing)
        setPos(x(), y()+15);
}


void Workers::move()
{


    if (targetFence->destroyed || targetFence->fenceHealth->getHealth() >= targetFence->fenceHealth->getMaxHealth())
    {
        qDebug() << "here";
        workerTimer->stop();
        delete this;
        return;
    }

    // move to the fence
    QPointF direction = targetFence->pos() - this->pos();
    direction /= QVector2D(direction).length();
    qreal dx = direction.x() * 10;
    qreal dy = direction.y() * 10;
    setPos(x() + dx, y() + dy);

    if (collidesWithItem(targetFence)) //if worker has reached fence
    {
        fixFence();
    }
}

void Workers::fixFence()
{
    if (targetFence->fenceType == "vertical")
    {
        if (this->x() > targetFence->x()) //on the left fence
            this->setPos(x() + 20, y());
        else
            this->setPos(x() - 20, y());


    }
    else
    {
        if (this->y() > targetFence->y()) //on the top fence
            this->setPos(x(), y() + 20);
        else
            this->setPos(x(), y() - 20);
    }

    if (targetFence->fenceHealth->getHealth() < targetFence->fenceHealth->getMaxHealth())
    {
        targetFence->fenceHealth->incrementHealth();
    }

}
