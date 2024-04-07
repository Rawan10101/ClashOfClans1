#ifndef PLAYER_H
#define PLAYER_H

#include <QDialog>

namespace Ui {
class Player;
}

class Player : public QDialog
{
    Q_OBJECT

public:
    explicit Player(QWidget *parent = nullptr);
    ~Player();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::Player *ui;


    bool isCannonSelected;
    QPoint selectedCannonPosition;

    void selectCannon(const QPoint& position);

};

#endif // PLAYER_H
