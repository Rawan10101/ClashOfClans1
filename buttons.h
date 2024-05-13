#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QObject>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QSoundEffect>

class pauseButton : public QPushButton
{
public:
    pauseButton();
};


class startMenuButtons : public QPushButton
{
public:
    startMenuButtons(QString text);
};

class Audio
{
    QSoundEffect* buttonSound;
    QSoundEffect* win;
    QSoundEffect* lose;
    QSoundEffect* bullet;
    QSoundEffect* enemyHit;
    QSoundEffect* booster;
    QSoundEffect* moneySound1;


public:
    Audio();
    void buttonClick();
    void winSound();
    void loseSound();
    void bulletSound();
    void enemyHitSound();
    void boosterSound();
    void setVolumes(qreal volume);
    void moneySound();


};

#endif // BUTTONS_H
