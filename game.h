#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QProgressBar>

#include <QGraphicsView>

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget *parent = nullptr);


    //explicit Game(QObject *parent = nullptr);
    void loadClanDesignFromFile(const QString& filePath);
    void printClanDesign();
    void displayClanDesign();

private:
    QVector<QVector<int>> clanDesign;
    QGraphicsScene* scene;
    QPushButton* setting;
    QProgressBar* money;
    QProgressBar* elixir;
};

#endif // GAME_H
