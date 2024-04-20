// #include "player.h"
// //#include "ui_player.h"
// #include <QMouseEvent> // Add this line

// Player::Player(QWidget *parent) :
//     QDialog(parent),
//   //  ui(new Ui::Player),
//     isCannonSelected(false)
// {
//    // ui->setupUi(this);
// }

// Player::~Player()
// {
//    // delete ui;
// }

// void Player::mousePressEvent(QMouseEvent *event)
// {
//     if (event->button() == Qt::LeftButton) {
//         if (!isCannonSelected) {
//             selectCannon(event->pos());
//         } else {
//             //launchCannonball(selectedCannonPosition, event->pos());
//             isCannonSelected = false;
//         }
//     }
// }

// void Player::selectCannon(const QPoint& position)
// {
//     selectedCannonPosition = position;
//     isCannonSelected = true;
// }
