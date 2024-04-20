// Game.h
#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGridLayout>
#include <QVector>

class QGraphicsScene;
class QGraphicsView;

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);

    void printClanDesign();
    void displayClanDesign();

private:
    QGridLayout *layout;
    QVector<QVector<int>> clanDesign;
    QGraphicsScene* scene;
    QGraphicsView* view;

    int cellSize;
    int sceneWidth;
    int sceneHeight;

    void adjustSceneSize();
    QPixmap scalePixmap(const QPixmap& pixmap, int width, int height);
};

#endif // GAME_H
