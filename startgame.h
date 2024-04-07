#ifndef STARTGAME_H
#define STARTGAME_H

#include <QDialog>
#include <QThread>
#include<QMediaPlayer>
#include<QGraphicsScene>
#include<QGraphicsView>
namespace Ui {
class StartGame;
}

class StartGame : public QDialog
{
    Q_OBJECT

public:
    explicit StartGame(QWidget *parent = nullptr);
    ~StartGame();

    void start_loading();
    QGraphicsScene* scene;

private slots:
    void on_pushButton_clicked();
    void on_groupBox_Background_clicked();
    void on_label_value_linkActivated(const QString &link);

private:
    Ui::StartGame *ui;
    QGraphicsView* view;

};

#endif // STARTGAME_H
