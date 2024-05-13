#ifndef GAME_H
#define GAME_H

#include "cannon.h"
#include "troop.h"
#include "fence1.h"
#include "townhall.h"
#include "health.h"
#include "bullet.h"
#include "levels.h"
#include "workers.h"
#include "playermoney.h"
// #include "shop.h"
#include "shop1.h"
#include "buttons.h"
#include "booster.h"


#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsTextItem>
#include <QMouseEvent>
#include <QRandomGenerator>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFrame>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QProgressBar>
#include <QTime>
#include <QGraphicsProxyWidget>
#include <QCoreApplication>
#include <QtNumeric>
#include <QMediaPlayer>
#include <QSoundEffect>
#include <QAudioOutput>
#include <QSlider>
#include <QCoreApplication>
#include <QQueue>
#include <QPair>
#include <QStack>
#include <unordered_map>

class shop;

class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);

private:

    static int townhallHealth;
    static int moneyupdated;
    //VARIABLES
    QRandomGenerator* randomGenerator;
    QVector<QVector<int>> clanDesign;
    Levels* level;
    QGridLayout *layout;
    QGraphicsScene* scene;
    QGraphicsView* view;

    startMenuButtons* startButton;
    startMenuButtons* shopButton;
    startMenuButtons* soundSettingsButton;
    pauseButton* pause;
    startMenuButtons* quitButton;
    startMenuButtons* helpButton;

    QMediaPlayer backgroundMusicPlayer;
    QAudioOutput audiooutput;
    QSoundEffect *bulletSoundEffect;

    bool gameStarted;
    bool townHallDestroyed;
    bool gamePaused = false;
    // bool clanBreached = false;
    QLabel* healthlabel2;
    QLabel* moneylabel2;

    QProgressBar* moneyBar;
    QLabel* moneyLabel;
    playerMoney* money;

    QProgressBar* healthBar;
    QLabel* healthLabel;


    QRectF timerRect;
    QGraphicsTextItem* timerText;
    QLabel* timerLabel;
    QTimer* timer;

    QTimer* m_timer;
    QTimer* spawnTimer;
    QTimer* workerTimer;
    QTimer* boosterTimer;

    Townhall* townhall;
    Cannon* cannon;
    Fence1* fence;


    int workerCount = 0;
    int killCount = 0;
    qreal cannonPower;

    // shop* shopWindow;
    Shop1* shopWindow;


    // Workers* worker;
    // int cellSize;
    // int sceneWidth;
    // int sceneHeight;
    //QProgressBar* timerBar;
    // int elapsedSeconds;
    QPixmap imageFence;
    QPixmap imageCannon;
    QPixmap imageTownhall;

    Audio* sounds;

    //FUNCTIONS
    void startLevel();
    void displayClanDesign();
    void startGame();
    // Townhall* findNearestTownhall(const QPointF& position);
    QVector<QPair<int, int>> findshortestPath(QPair<int,int> troopPosition);
    void checkCollisions(Troop* troop);
    void resetTimer();
    void mousePressEvent(QMouseEvent *event);
    // void checkCollisionsworkers(Workers* worker);
    // void rebuildStructures();
    // void handleShopButton();
    QList<QGraphicsItem*> itemsToRemove;
    QLabel* name;

public slots:
    void updateMoney(int newMoney);
    void updateimagehealth(QString type, QPixmap image, int health2);


private slots:

    void handleStartButton();
    void handleSoundSettingsButton();
    void handlePauseButton();
    void handleQuitButton();
    void handleHelpButton();
    void formTroops();
    void moveTroops();
    void updateTimer();
    // void onFenceRepaired(Fence1* fence);
    void showShopWindow();
    // void moveWorkers();
    void showPauseMenu();
    void spawnBoosters();

private slots:
    void removeMarkedItems();

};

#endif // GAME_H
