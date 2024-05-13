#include "buttons.h"

pauseButton::pauseButton()
{
    setFixedSize(80, 80);
    setStyleSheet("QPushButton { border-radius : 40px; background-color : transparent; }");
    setIcon(QIcon(":/images/pause.png"));
    setIconSize(QSize(80, 80));
    setFlat(false);
}

startMenuButtons::startMenuButtons(QString text)
{
    setText(text);
    setStyleSheet("background-color: rgb(42, 44, 62); color: rgb(255, 255, 255); font: 20px;");
}

Audio::Audio()
{
    buttonSound = new QSoundEffect;
    buttonSound->setSource(QUrl("qrc:/Sound files/buttonclick.wav"));
    buttonSound->setVolume(20);

    win = new QSoundEffect;
    win->setSource(QUrl("qrc:/Sound files/win.wav"));
    win->setVolume(20);

    lose = new QSoundEffect;
    lose->setSource(QUrl("qrc:/Sound files/lose.wav"));
    lose->setVolume(20);

    bullet = new QSoundEffect;
    bullet->setSource(QUrl("qrc:/Sound files/bullet.wav"));
    bullet->setVolume(10);

    enemyHit = new QSoundEffect;
    enemyHit->setSource(QUrl("qrc:/Sound files/enemyHit.wav"));
    enemyHit->setVolume(10);

    booster = new QSoundEffect;
    booster->setSource(QUrl("qrc:/Sound files/booster.wav"));
    booster->setVolume(5);

    moneySound1=new QSoundEffect;
    moneySound1->setSource(QUrl("qrc:/../../../Voicy_Coins-collect-Clash-of-Clans.wav"));
    moneySound1->setVolume(5);
}

void Audio::buttonClick()
{
    buttonSound->play();
}

void Audio::moneySound()
{
    moneySound1->play();
}

void Audio::winSound()
{
    win->play();
}

void Audio::loseSound()
{
    lose->play();
}

void Audio::bulletSound()
{
    bullet->play();
}

void Audio::enemyHitSound()
{
    enemyHit->play();
}

void Audio::boosterSound()
{
    booster->play();
}
void Audio::setVolumes(qreal volume)
{
    buttonSound->setVolume(volume);
    win->setVolume(volume);
    lose->setVolume(volume);
    bullet->setVolume(volume);
    enemyHit->setVolume(volume);
}
