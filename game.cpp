#include "Game.h"

using namespace std;

Game::Game(QWidget *parent) : QWidget(parent)
{
    int seed = QDateTime::currentMSecsSinceEpoch(); //seeding randomgenerator for troop spawning
    randomGenerator = new QRandomGenerator(seed);

    level = new Levels; //creating an instance of level
    layout = new QGridLayout(this);
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    view->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    money = new playerMoney;
    shopWindow = new Shop1(this, money->getCurrentMoney());
    layout->deleteLater();

    setLayout(layout);

    //setting background
    QPixmap backgroundPixmap(":/images/bg.jpg"); //background image is empty field
    if (!backgroundPixmap.isNull())
    {
        view->setBackgroundBrush(backgroundPixmap);
    }

    //layout
    setLayout(layout);
    view->setStyleSheet("background: transparent; border: 0px");
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(view);
    view->show();

    //buttons
    startButton = new startMenuButtons("Start Level " + QString::number(level->currLevel));
    connect(startButton, SIGNAL(clicked()), this, SLOT(handleStartButton()));

    shopButton = new startMenuButtons("Shop");
    connect(shopButton, SIGNAL(clicked()), this, SLOT(showShopWindow()));
    connect(shopWindow, &Shop1::moneyChanged, this, &Game::updateMoney);
    connect(shopWindow, &Shop1::imagehealthChanges, this, &Game::updateimagehealth);

    soundSettingsButton = new startMenuButtons("Sound Settings");
    connect(soundSettingsButton, SIGNAL(clicked()), this, SLOT(handleSoundSettingsButton()));

    helpButton = new startMenuButtons("How To Play?");
    connect(helpButton, SIGNAL(clicked()), this, SLOT(handleHelpButton()));

    quitButton = new startMenuButtons("Quit");
    connect(quitButton, SIGNAL(clicked()), this, SLOT(handleQuitButton()));

    fence= new Fence1("");

    gameStarted = false;

    healthBar= new QProgressBar(this);
    healthBar->setTextVisible(false);
    healthBar->setGeometry(13,65,60,20);
    healthBar->setRange(0,1000);
    townhall= new Townhall;
    healthBar->setValue(townhallHealth);
    healthLabel = new QLabel(this);
    healthLabel->setGeometry(80,65,60,15);
    healthLabel->setText(QString::number(townhall->townhallHealth->getHealth()));

    healthBar->hide();
    healthLabel->hide();

    healthlabel2= new QLabel(this);
    healthlabel2->setGeometry(13,47,60,15);
    healthlabel2->setText("Health");
    healthBar->setStyleSheet("QProgressBar {"
                            "border: 2px solid grey;"
                            "border-radius: 5px;"
                            "background-color: pink;" // Change color here
                            "}"
                            "QProgressBar::chunk {"
                            "background-color: green;" // Change color here
                            "}");
    healthBar->hide();
    healthLabel->hide();
    healthlabel2->hide();

    startLevel(); //sets scene and view and clan design

    //-----------------------------------------------//

    //TIMER LABEL
    timerRect = QRectF(10, 10, 100, 40);
    timerText = new QGraphicsTextItem();
    timerText->setPos(timerRect.bottomLeft());
    timerText->setPlainText("0:00");
    timerText->setDefaultTextColor(Qt::black);
    timerText->setFont(QFont("Arial", 20));
    timerText->setOpacity(0.8);
    timerText->setPos(0, 440);
    scene->addItem(timerText);
    timerText->hide();



    //Money will increase when player wins a level
    moneyupdated=money->getCurrentMoney();

    moneyBar= new QProgressBar(this);
    moneyBar->setTextVisible(false);
    moneyBar->setGeometry(12,27,60,20);
    moneyBar->setRange(0,1000);
    moneyBar->setValue(moneyupdated);
    moneyBar->setStyleSheet("QProgressBar {"
                            "border: 2px solid grey;"
                            "border-radius: 5px;"
                            "background-color: pink;" // Change color here
                            "}"
                            "QProgressBar::chunk {"
                            "background-color: green;" // Change color here
                            "}");
    moneyLabel = new QLabel(this);
    moneyLabel->setGeometry(80,27,60,20);
    moneyLabel->setText(QString::number(moneyupdated));

    moneylabel2= new QLabel(this);
    moneylabel2->setGeometry(13,7,60,20);
    moneylabel2->setText("Money");

    moneyBar->hide();
    moneyLabel->hide();
    moneylabel2->hide();


    backgroundMusicPlayer.setAudioOutput(&audiooutput);
    backgroundMusicPlayer.setSource(QUrl("qrc:/Sound files/background music.mp3"));
    backgroundMusicPlayer.play();

    // bulletSoundEffect = new QSoundEffect();
    // bulletSoundEffect->setSource(QUrl("qrc:/sounds/bullet_sound.wav"));
    // bulletSoundEffect->setVolume(50);

    sounds = new Audio;
    name= new QLabel;


}

int Game::townhallHealth = 1000;
int Game::moneyupdated = 0;

void Game::updateMoney(int newMoney)
{
    qDebug()<<"Money Updated"<< moneyupdated;
    money->setMoney(moneyupdated);
    moneyupdated=money->getCurrentMoney() - newMoney;
    moneyBar->setValue(money->getCurrentMoney() - newMoney);
    moneyLabel->setText(QString::number(money->getCurrentMoney() - newMoney));
    money->setMoney(money->getCurrentMoney() - newMoney);
    sounds->moneySound();
    qDebug()<<"Money"<< money->getCurrentMoney();
    qDebug()<<"NewMoney"<< newMoney;
}

void Game::updateimagehealth(QString type, QPixmap image, int health2)
{

    if(type == "Fence"){
        imageFence=image;
        fence->fenceHealth->setMaxHealth(health2);
    }
    else if(type == "Cannon"){
        imageCannon=image;
    }
    else if(type == "Townhall"){
        imageTownhall = image;
      townhallHealth = health2;
    }

}

void Game::startLevel()
{
    QGraphicsProxyWidget* startBtn = scene->addWidget(startButton);
    QGraphicsProxyWidget* shopBtn = scene->addWidget(shopButton);
    QGraphicsProxyWidget* settingsBtn = scene->addWidget(soundSettingsButton);
    QGraphicsProxyWidget* quitBtn = scene->addWidget(quitButton);
    QGraphicsProxyWidget* helpBtn = scene->addWidget(helpButton);

    startButton->setMinimumWidth(soundSettingsButton->width());
    shopButton->setMinimumWidth(soundSettingsButton->width());
    quitButton->setMinimumWidth(soundSettingsButton->width());
    helpButton->setMinimumWidth(soundSettingsButton->width());

    startBtn->setPos(view->width() / 2 - startButton->width() / 2, view->height() - view->height() / 2);
    shopBtn->setPos(view->width() / 2 - shopButton->width() / 2, startBtn->y() + startButton->height() + 10);
    settingsBtn->setPos(view->width() / 2 - soundSettingsButton->width() / 2, shopBtn->y() + shopButton->height() + 10);
    helpBtn->setPos(view->width() / 2 - quitButton->width() / 2, settingsBtn->y() + soundSettingsButton->height() + 10);
    quitBtn->setPos(view->width() / 2 - quitButton->width() / 2, helpBtn->y() + helpButton->height() + 10);


    startButton->setText("Start Level " + QString::number(level->currLevel)); //to update start button text
    startButton->setEnabled(true);
    shopButton->setEnabled(true);
    soundSettingsButton->setEnabled(true);
    quitButton->setEnabled(true);
    helpButton->setEnabled(true);

    gameStarted = false;
    townHallDestroyed = false;
    gamePaused = false;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer())); //game timer

    m_timer = new QTimer(this); //troop movement timer
    connect(m_timer,SIGNAL(timeout()),this,SLOT (moveTroops()));

    spawnTimer = new QTimer(); //spawning troops timer
    connect(spawnTimer, SIGNAL(timeout()),this, SLOT (formTroops()));

    boosterTimer = new QTimer(); //spawning boosters (health markers)
    connect(boosterTimer, SIGNAL(timeout()), this, SLOT(spawnBoosters()));

    clanDesign = level->getDesignVector(); //sends a vector for the clan design based on the current level

    scene->setSceneRect(0, 0, clanDesign[0].size() * 50, clanDesign.size() * 50); //set scene and view
    view->setFixedSize(clanDesign[0].size() * 50, clanDesign.size() * 50);

    //----------------------------------------------//

    startButton->show();
    shopButton->show();
    soundSettingsButton->show();
    helpButton->show();
    quitButton->show();
    healthBar->hide();
    healthLabel->hide();
    healthlabel2->hide();
}

void Game::displayClanDesign()
{
    const int tileSize = 50;
    const int fenceSize = tileSize ;
    const int castleSize = tileSize;
    const int cannonSize = tileSize;

    qDebug()<< "inside displayClanDesign";

    for (int i = 0; i < clanDesign.size(); i++)
    {
        for (int j = 0; j < clanDesign[i].size(); j++)
        {
            int element = clanDesign[i][j]; //element at the current position

            if (element == 2) // townhall
            {
                if(!imageTownhall.isNull())
               //  townhall->setPix1(imageTownhall);

                townhall = new Townhall();
                townhall->setPos(j * castleSize, i * castleSize);
                townhall->GridPosition.first = i; townhall->GridPosition.second = j;
                scene->addItem(townhall);

            }
            else if (element == 3) // cannon
            {
                if(imageCannon.isNull()){
                    cannon = new Cannon();
                    cannon->setPos(j * cannonSize, i * cannonSize);
                    scene->addItem(cannon);
                }
                else
                {
                    cannon = new Cannon();
                    cannon->setPos(j * cannonSize, i * cannonSize);
                    scene->addItem(cannon);
                    cannon->setPix(imageCannon);
                }

            }
            else if (element == 4) // fence
            {

                //find out whether fence is horizontal or vertical
                if (clanDesign[i-1][j] == 4 || clanDesign[i+1][j] == 4)
                  fence = new Fence1("vertical");
                else
                   fence = new Fence1("horizontal");


                if (!imageFence.isNull())
                    fence->setPix(imageFence);

                fence->setPos(j * fenceSize, i * fenceSize);
                scene->addItem(fence);

            }
        }
    }
}

void Game::handleStartButton()
{
    if (!gameStarted)
    {
        startButton->setEnabled(false);
        gameStarted = true;
        startButton->hide();
        shopButton->hide();
        startGame();
        sounds->buttonClick();
    }

}

void Game::startGame()
{
    workerCount = 0;
    killCount = 0;

    startButton->hide();
    shopButton->hide();
    soundSettingsButton->hide();
    helpButton->hide();
    quitButton->hide();

    healthBar->show();
    healthLabel->show();
    timerText->show();
    moneyBar->show();
    moneyLabel->show();
    moneylabel2->show();
    healthlabel2->show();
    resetTimer();
    timer->start(1000);
    boosterTimer->start(30000);
    displayClanDesign();

    moneyBar->setValue(moneyupdated);
    moneyLabel->setText(QString::number(moneyupdated));

    pause = new pauseButton;
    QGraphicsProxyWidget * pauseBtn = scene->addWidget(pause);
    pauseBtn->setPos(scene->width() - pause->width(), 0);
    connect(pause, SIGNAL(clicked()), this, SLOT(handlePauseButton()));

    backgroundMusicPlayer.play();

    townhall->townhallHealth->setMaxHealth(townhallHealth);
    healthBar->setValue(townhallHealth);
    healthLabel->setText(QString::number(townhallHealth));

    if (level->currLevel == 1) {//enemies spawn more frequently as level increases
        spawnTimer->start(4000);
        // townhall->townhallHealth->setMaxHealth(townhallHealth);
        // healthBar->setValue(townhallHealth);
        // healthLabel->setText(QString::number(townhallHealth));
    }

    else if (level->currLevel == 2) {
        spawnTimer->start(3000);
        // townhall->townhallHealth->setMaxHealth(townhallHealth);
        // healthBar->setValue(townhallHealth);
        // healthLabel->setText(QString::number(townhallHealth));
    }

    else if (level->currLevel == 3) {
        spawnTimer->start(2000);

    }
    else if (level->currLevel == 4) {
        spawnTimer->start(1000);

    }
    else if (level->currLevel == 5) {
        spawnTimer->start(500);

    }

}

void Game::formTroops()
{
    int randomX;
    int randomY;

    do{
        randomX = randomGenerator->bounded(0, clanDesign[0].size()-1); //generating a random X and Y within scene dimensions
        randomY = randomGenerator->bounded(0, clanDesign.size()-1);
         // qDebug()<< randomX << " " << randomY;
    } while (clanDesign[randomY][randomX] != 0); //keeps generating until position is a 0

    qDebug() << "randomX: " << randomX << " randomY: " << randomY;
    Troop* troop = new Troop(level->currLevel * 300, level->currLevel * 100, level->currLevel);
    scene->addItem(troop);
    troop->setPos(randomX * 50, randomY * 50);
    troop->currGridPosition.first = randomY; troop->currGridPosition.second = randomX;
    //i is Y, j is X
    //currGridPosition represents the troop's position on the clanDesign grid (used for shortest path)
    troop->Path = findshortestPath(troop->currGridPosition);

    if (level->currLevel == 1) //enemies move faster as level increases
        m_timer->start(30);

    else if (level->currLevel == 2)
        m_timer->start(25);

    else if (level->currLevel == 3)
        m_timer->start(20);

    else if (level->currLevel == 4)
        m_timer->start(15);

    else if (level->currLevel == 5)
        m_timer->start(10);

}

void Game::moveTroops()
{

    foreach(QGraphicsItem* item, scene->items())
    {
        Troop* troop = dynamic_cast<Troop*>(item);
        if (troop)
        {
                if (!troop->Path.empty())
                {
                    qreal nextStepX = troop->Path.first().second * 50;
                    qreal nextStepY = troop->Path.first().first * 50;
                    QPointF nextStep;
                    nextStep.setX(nextStepX);
                    nextStep.setY(nextStepY);
                    QPointF direction = nextStep - troop->pos();
                    direction /= QVector2D(direction).length();
                    qreal dx = direction.x();
                    qreal dy = direction.y();
                    troop->setPos(troop->x() + dx, troop->y() + dy);
                    if (QVector2D(nextStep - troop->pos()).length() < 1)
                        troop->Path.pop_front();
                }

            checkCollisions(troop);
        }

    }

}



QVector<QPair<int, int>> Game::findshortestPath(QPair<int,int> troopPosition) //returns a vector of the coordinates in the path
{

        QVector<QVector<int>> tempMap = clanDesign; //to create a map with 0s in place of the destroyed fences

        for (int y = 0; y < tempMap.size(); y++)
            for (int x = 0; x < tempMap[0].size(); x++)
            {
                if (tempMap[y][x] == 4 && scene->items(QPointF(x * 50, y * 50)).isEmpty()) //if there is a fence there and it is destroyed, add 0 instead
                    tempMap[y][x] = 0;
            }


    QVector<QVector<int>> distMap(tempMap.size(), QVector<int>(tempMap[0].size(),INT_MAX)); //creates graph of distances from clan design and initializes all to int_max
    map<QPair<int, int>, QPair<int, int>> originMap; //to store the path. i used map instead of unordered map so i can store QPairs


    QVector<QPair<int, int>> queue;
    queue.push_back(troopPosition);

    distMap[troopPosition.first][troopPosition.second] = 0;

    while (!queue.empty()) //BFS
    {
        QPair<int,int>
            current = queue.front();
        queue.pop_front();

        int i = current.first;
        int j = current.second;

        // qDebug() << "i: " << i << " j: " << j;
        if (current == townhall->GridPosition)
            break;

        QVector<QPair<int, int>> adjList =
            { {i + 1, j}, {i - 1, j}, {i, j + 1}, {i, j - 1}, //up down left right
              {i - 1, j + 1}, {i + 1, j + 1}, {i - 1, j -1}, {i + 1, j - 1}}; //diagonals

        for (const auto& adjacent: adjList)
        {
            int adjI = adjacent.first;
            int adjJ = adjacent.second;

            // qDebug() << "adjI: " << adjI << " adjJ: " << adjJ;
            if (adjI < tempMap.size() && adjI >= 0 && adjJ < tempMap[0].size() && adjJ >= 0) //to avoid going out of bounds of the vector dimensions
            {
                // qDebug() << "distMap[adjI][adjJ]: " << distMap[adjI][adjJ] << " distMap[i][j]: " << distMap[i][j] << "tempMap[adjI][adjJ]: " << tempMap[adjI][adjJ];
                if (distMap[adjI][adjJ] > distMap[i][j] + tempMap[adjI][adjJ]) //check if distance is shorter
                {
                    // qDebug()<< "here";

                    distMap[adjI][adjJ] = distMap[i][j] + tempMap[adjI][adjJ]; //update
                    originMap[adjacent] = current; //add to paths
                    queue.push_back(adjacent); //to continue BFS
                }
            }
        }


    }

    QVector<QPair<int, int>> shortestPath;
    QPair<int, int> current = townhall->GridPosition;

    while (current != troopPosition) //backtrack to create path in a vector in order
    {
        shortestPath.push_back(current);
        current = originMap[current];
    }

    // qDebug()<< "shortestPath.count()" << shortestPath.count();
    reverse(shortestPath.begin(), shortestPath.end()); //to reverse the path
    shortestPath.push_back(townhall->GridPosition); //to add the destination to the vector

    return shortestPath;

}

void Game::checkCollisions(Troop* troop)
{
    QList<QGraphicsItem*> collidingItems = troop->collidingItems();
    // QList<QGraphicsItem*> itemsToRemove;

    foreach (QGraphicsItem* collidingItem, collidingItems)
    {
        if (typeid(*collidingItem) == typeid(Bullet))
        {
            sounds->enemyHitSound();

            // qDebug() << cannon->currPower;
            troop->troopHealth->reduceHealth(cannon->currPower);
            troop->knockBack(collidingItem->pos().x(), collidingItem->pos().y());

            if (troop->troopHealth->getHealth() <= 0)
            {

                // itemsToRemove.append(troop);
                // qDebug() << cannon->currPower;
                itemsToRemove.append(collidingItem);
                itemsToRemove.append(troop);
                killCount++;
                if (killCount == 20)
                {
                    // qDebug() << "cannon powerup";
                    cannon->powerUp();
                    killCount = 0; //reset count to 0 to allow for more powerups
                }
            }
        }

        else if (typeid(*collidingItem) == typeid(Townhall))
        {
            Townhall *townhall = dynamic_cast<Townhall*>(collidingItem);
            // qDebug() << "townhall health:" << townhall->healthValue;
            // qDebug() << "troop power:" << troop->troopPower;

            if(townhall){
                qreal dx = troop->x() - collidingItem->x();
                qreal dy = troop->y() - collidingItem->y();

                  if (qAbs(dx) > qAbs(dy))//move left or right
                {
                    if (dx < 0) //move left
                        troop->setPos(townhall->x()-60, townhall->y());
                    else //move right
                        troop->setPos(townhall->x()+60, townhall->y());
                }
                else //move up or down
                {
                    if (dy < 0) //move up
                        troop->setPos(townhall->x(), townhall->y()-60);
                    else //move down
                        troop->setPos(townhall->x(), townhall->y()+60);
                }

                if ( townhall && typeid(*collidingItem) == typeid(Townhall))
                {
                    townhall->townhallHealth->reduceHealth(troop->troopPower);

                    healthBar->setValue(townhall->townhallHealth->getHealth());

                    healthLabel->setText(QString::number(townhall->townhallHealth->getHealth()));
                    // qDebug()<< townhall->townhallHealth->getHealth();
                    if (townhall->townhallHealth->getHealth() <= 0)
                    {
                        // itemsToRemove.append(townhall);
                        itemsToRemove.append(collidingItem);
                        townHallDestroyed = true;
                        // count++;
                    }
                 }
            }
            if(townHallDestroyed){
                healthBar->setValue(0);
                healthLabel->setText(QString::number(0));
            }
        }
        else if (typeid(*collidingItem) == typeid(Workers))
        {
            Workers* worker = new Workers;
            itemsToRemove.append(collidingItem);
            itemsToRemove.append(worker);
            workerCount--;
        }

        else if (typeid(*collidingItem) == typeid(Fence1))
        {
            Fence1* fence = dynamic_cast<Fence1*>(collidingItem);
            // qDebug() << "fence health:" << fence->healthValue;
            // qDebug() << "troop power:" << troop->troopPower;

            if(fence)
            {
                // qDebug() << "fence collision";

                if (fence->fenceType == "vertical") //side
                {
                    if (troop->x() > fence->x())
                        troop->setPos(troop->x() + 30, troop->y());
                    else
                        troop->setPos(troop->x() - 30, troop->y());
                }
                else
                {
                    if (troop->y() > fence->y())
                        troop->setPos(troop->x(), troop->y() + 30);
                    else
                        troop->setPos(troop->x(), troop->y() - 30);

                }

                // qDebug() << "Collision with Fence1";
                fence->markForRemoval();

                if (fence && typeid(*collidingItem) == typeid(Fence1))
                {
                    fence->fenceHealth->reduceHealth(troop->troopPower);
                    // qDebug() << fence->fenceHealth->getHealth();

                        if (fence->fenceHealth->getHealth() <= 0)
                        {
                            // itemsToRemove.append(fence);
                            itemsToRemove.append(collidingItem);
                            // clanBreached = true;
                            fence->destroyed = true;
                            workerCount--;
                        }
                        else
                        {
                            if (workerCount < 5 && !fence->underRepair)
                            {
                                Workers* worker = new Workers;
                                worker->setPos(townhall->x(), townhall->y());
                                scene->addItem(worker);
                                // worker->targetFence = fence;
                                worker->setFence(fence);
                                worker->workerTimer->start(250);
                                workerCount++;
                                fence->underRepair = true;
                                // qDebug()<< fence->fenceHealth;
                            }
                        }

                }

            }
        }


    }


    QTimer::singleShot(0, this, &Game::removeMarkedItems);
}

void Game::removeMarkedItems()
{
    foreach (QGraphicsItem* item, itemsToRemove)
    {
        scene->removeItem(item);
        delete item;
    }
    itemsToRemove.clear();
}

void Game::updateTimer()
{
    QTime currentTime = QTime::fromString(timerText->toPlainText(), "m:ss");

    currentTime = currentTime.addSecs(1);
    timerText->setPlainText(currentTime.toString("m:ss"));

    if (currentTime.second() == 10 )
    {
        sounds->winSound();

        timer->stop();
        m_timer->stop();
        spawnTimer->stop();
        boosterTimer->stop();
        foreach (QGraphicsItem* item, scene->items())
        {
            if (typeid(*item) == typeid(Workers))
            {
                Workers* w = dynamic_cast<Workers*>(item);
                w->workerTimer->stop();
            }
        }
        foreach (QGraphicsItem* item, scene->items())
        {
            if (typeid(*item) == typeid(Workers))
            {
                Workers* w = dynamic_cast<Workers*>(item);
                w->dance();

            }
        }
        QMessageBox::information(this, "Player wins!", "Level " + QString::number(level->currLevel) + " completed succesfully!");
        if (level->currLevel == 5)
        {
            QMessageBox* endGame = new QMessageBox;
            endGame->setWindowFlags(Qt::CustomizeWindowHint);
            endGame->setText("Congratulations!\nYou have completed all five levels\nand successfully protected your cake from the pests!");
            endGame->setStyleSheet("background-color: rgb(42, 44, 62); color: white;");
            QPushButton* quit = new QPushButton("Exit Game");
            endGame->addButton(quit, QMessageBox::ActionRole);
            endGame->exec();
            if (endGame->clickedButton() == quit)
                QCoreApplication::quit();
        }
        level->nextLevel(); //increment current level

        moneyupdated = money->currentMoney + 100;
        money->setMoney(moneyupdated);
        moneyLabel->setText(QString::number(moneyupdated));
        moneyBar->setValue(moneyupdated);
        sounds->moneySound();
        foreach (QGraphicsItem* items, scene->items())
        {
            //clear clan design to prepare for next level
            if (typeid(*items) == typeid(Fence1) || typeid(*items) == typeid(Workers) || typeid(*items) == typeid(Troop) || typeid(*items) == typeid(Cannon) || typeid(*items) == typeid(Townhall) || typeid(*items) == typeid(Booster))
            {
                items->hide();
                delete items;
            }
        }

        resetTimer();
        pause->hide();
        startLevel(); //starts next level
    }

    else if(townHallDestroyed == true){
        sounds->loseSound();
        timer->stop();
        m_timer->stop();
        spawnTimer->stop();
        boosterTimer->stop();

        foreach (QGraphicsItem* item, scene->items())
        {
            if (typeid(*item) == typeid(Workers))
            {
                Workers* w = dynamic_cast<Workers*>(item);
                w->workerTimer->stop();
            }
        }

        foreach (QGraphicsItem* item, scene->items())
        {
            if (typeid(*item) == typeid(Troop))
            {
                Troop* t = dynamic_cast<Troop*>(item);
                t->dance();

            }
        }

        QMessageBox::information(this, "Game Over", "Game Over"); //!!HANDLE THE BUTTONS!!
        foreach (QGraphicsItem* items, scene->items())
        {
            //clear clan design to prepare for next level
            if (typeid(*items) == typeid(Fence1) || typeid(*items) == typeid(Workers) || typeid(*items) == typeid(Troop) || typeid(*items) == typeid(Cannon) || typeid(*items) == typeid(Townhall))
                delete items;
        }


        resetTimer();
        pause->hide();
        startLevel(); //restarts the level
    }

}

void Game::resetTimer()
{
    timerText->setPlainText("0:00");
}

void Game::mousePressEvent(QMouseEvent *event) //release bullet when player clicks left
{
    if (event->button() == Qt::LeftButton)
    {
        if (!gameStarted)
        {
            return;
        }

        sounds->bulletSound();
        // QPointF targetPos = event->pos();
        QPoint targetPos = QCursor::pos();
        qreal dx = targetPos.x() - cannon->pos().x();
        qreal dy = targetPos.y() - cannon->pos().y();
        qreal length = qSqrt(dx * dx + dy * dy);
        qreal directionX = dx / length;
        qreal directionY = dy / length;

        // qDebug() << "Direction X:" << directionX << "Direction Y:" << directionY;

        Bullet *bullet = new Bullet(targetPos.x(), targetPos.y(), cannon->pos().x() , cannon->pos().y());
        bullet->setDirection(directionX, directionY);

        bullet->setPos(cannon->pos().x(), cannon->pos().y()); //bullet comes out of cannon

        scene->addItem(bullet);

        ///////////////
        // qDebug() << "cannon power: " << cannon->power;
    }
}


void Game::showShopWindow()
{
    shopWindow->show();
    sounds->buttonClick();
}

void Game::handleSoundSettingsButton()
{
    QDialog* soundSettingsDialog = new QDialog(this);
    soundSettingsDialog->setWindowTitle("Sound Settings");

    QVBoxLayout* layout = new QVBoxLayout(soundSettingsDialog);

    QLabel* volumeLabel = new QLabel("Volume");
    QSlider* volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(int( 100));

    QPushButton* applyButton = new QPushButton("Apply");

    layout->addWidget(volumeLabel);
    layout->addWidget(volumeSlider);
    layout->addWidget(applyButton);

    connect(applyButton, &QPushButton::clicked, soundSettingsDialog, &QDialog::accept);
    connect(volumeSlider, &QSlider::valueChanged, this, [this](int value) {
        qreal volume = qreal(value) / 100.0;
        audiooutput.setVolume(volume);
    });

    if (soundSettingsDialog->exec() == QDialog::Accepted)
    {
        int volume = volumeSlider->value();
        QMessageBox::information(this, "Sound Settings", "Volume changed to " + QString::number(volume));
    }

    delete soundSettingsDialog;
    if (!gameStarted)
        showPauseMenu();
}



void Game::handlePauseButton()
{
    if (!gamePaused)
    {
        sounds->buttonClick();

        qDebug()<< "pause";
        gamePaused = true;
        timer->stop();
        m_timer->stop();
        spawnTimer->stop();
        boosterTimer->stop();
        foreach (QGraphicsItem* item, scene->items())
        {
            if (typeid(*item) == typeid(Workers))
            {
                Workers* w = dynamic_cast<Workers*>(item);
                w->workerTimer->stop();
            }
        }

        showPauseMenu();

    }
    else
    {
        qDebug()<< "play";
        gamePaused = false;
        timer->start();
        m_timer->start();
        spawnTimer->start();
        boosterTimer->start();
        foreach (QGraphicsItem* item, scene->items())
        {
            if (typeid(*item) == typeid(Workers))
            {
                Workers* w = dynamic_cast<Workers*>(item);
                w->workerTimer->start();
            }
        }

    }
}

void Game::handleQuitButton()
{
    sounds->buttonClick();

    QMessageBox* confirmQuit = new QMessageBox;
    confirmQuit->setWindowFlags(Qt::CustomizeWindowHint);
    confirmQuit->setText("Are you sure you would like to quit?");
    confirmQuit->setStyleSheet("background-color: rgb(42, 44, 62); color: white;");

    QPushButton* cancel = new QPushButton("Cancel");
    confirmQuit->addButton(cancel, QMessageBox::ActionRole);
    QPushButton* quit = new QPushButton("Quit");
    confirmQuit->addButton(quit, QMessageBox::ActionRole);
    confirmQuit->exec();

    if (confirmQuit->clickedButton() == cancel)
    {
        sounds->buttonClick();

        delete confirmQuit;
    }
    else
        QCoreApplication::quit();
}

void Game::handleHelpButton()
{
    sounds->buttonClick();

    QMessageBox* helpWindow = new QMessageBox;
    helpWindow->setWindowFlags(Qt::CustomizeWindowHint);
    //////////////////////////////////////////////////////////
    helpWindow->setText("Your base is under attack!\n\n"
                        "Game Objective: Protect your town hall from enemy troops.\n\n"
                        "-Shoot and kill enemy troops by left-clicking.\n\n"
                        "-You have five citizen workers defending your base by repairing fences.\n\n"
                        "-The game is over when enemy troops destroy your town hall and you lose,\n\n"
                        "-Or when the time is up with your town hall still standing and you win.\n\n"
                        "-Power boosters spawn randomly, try to catch them to boost your cannon power for 30 seconds!\n\n"
                        "-Once you have enough money, head on over to the shop for some upgrades\n\n"
                        "-Good luck!");
    helpWindow->setStyleSheet("background-color: rgb(42, 44, 62); color: white;");

    QPushButton* OK = new QPushButton("OK");
    helpWindow->addButton(OK, QMessageBox::RejectRole);
    helpWindow->exec();

    if (gamePaused)
        showPauseMenu();

}

void Game::showPauseMenu()
{
    //still not done yet
    QMessageBox* menu = new QMessageBox;
    menu->setWindowFlags(Qt::CustomizeWindowHint);
    menu->setText("Game Options");
    menu->setStyleSheet("background-color: rgb(42, 44, 62); color: white;");

    QPushButton* resume = new QPushButton("Resume");
    menu->addButton(resume, QMessageBox::ActionRole);
    QPushButton* sound = new QPushButton("Sound Settings");
    menu->addButton(sound, QMessageBox::ActionRole);
    QPushButton* help = new QPushButton("Help");
    menu->addButton(help, QMessageBox::ActionRole);
    QPushButton* leave = new QPushButton("Back to Main Menu");
    menu->addButton(leave, QMessageBox::ActionRole);
    menu->exec();
    if (menu->clickedButton() == resume)
    {
        sounds->buttonClick();

        handlePauseButton(); //will resume
        delete menu;
    }
    if (menu->clickedButton() == sound)
    {
        sounds->buttonClick();

        handleSoundSettingsButton();
    }
    if (menu->clickedButton() == help)
    {
        sounds->buttonClick();

        handleHelpButton();
    }
    if (menu->clickedButton() == leave)
    {
        sounds->buttonClick();

        QMessageBox* confirmLeave = new QMessageBox;
        confirmLeave->setWindowFlags(Qt::CustomizeWindowHint);
        confirmLeave->setText("Are you sure you would like to return to main menu?\nYour progress in this level will not be saved");
        confirmLeave->setStyleSheet("background-color: rgb(42, 44, 62); color: white;");

        QPushButton* cancel = new QPushButton("Cancel");
        confirmLeave->addButton(cancel, QMessageBox::RejectRole);
        QPushButton* yes = new QPushButton("Leave");
        confirmLeave->addButton(yes, QMessageBox::ActionRole);
        confirmLeave->exec();

        if (confirmLeave->clickedButton() == yes)
        {
            sounds->buttonClick();

            foreach (QGraphicsItem* items, scene->items())
            {
                //clear clan design
                if (typeid(*items) == typeid(Fence1) || typeid(*items) == typeid(Workers) || typeid(*items) == typeid(Troop) || typeid(*items) == typeid(Cannon) || typeid(*items) == typeid(Townhall))
                    delete items;
            }
            resetTimer();
            pause->hide();
            startLevel(); //restarts the level
            delete confirmLeave;
        }
        else
        {
            sounds->buttonClick();

            showPauseMenu();
            delete confirmLeave;
        }

    }
}

void Game::spawnBoosters()
{
    qDebug() << "in spawnboosters";
    int spawn = randomGenerator->bounded(0,2);
    qDebug() << spawn;
    if (spawn == 0)
        return;
    else
    {
        int randomX;
        int randomY;

        do{
                randomX = randomGenerator->bounded(0, clanDesign[0].size()-1); //generating a random X and Y within scene dimensions
                randomY = randomGenerator->bounded(0, clanDesign.size()-1);
                qDebug()<< randomX << " " << randomY;
        } while (!(clanDesign[randomY][randomX] == 0 || clanDesign[randomY][randomX] == 1) ); //keeps generating until position is a 0 or 1

        Booster* booster = new Booster;
        scene->addItem(booster);
        booster->setPos(randomY * 50, randomX * 50);
    }
}



