#ifndef SHOP1_H
#define SHOP1_H

#include <QDialog>
#include <QObject>
#include <QWidget>
#include "townhall.h"
#include "playermoney.h"
#include "cannon.h"
#include "fence1.h"
#include <QDialog>
#include <QStackedLayout>


namespace Ui {
class Shop1;
}

class Shop1 : public QDialog
{
    Q_OBJECT

public:
    explicit Shop1(QWidget *parent = nullptr,int money1=0);
    ~Shop1();
    playerMoney* money;
    Townhall* town;
    Cannon* cannon;
    Fence1* fence;
    int currentMoney;
    int newMoney;
    QString type;
    int sendMoney();
private slots:
    void on_townHall_clicked();

    // void on_fence_clicked(const QPixmap& newImage, int newHealth);

    // void on_cannon_clicked(const QPixmap& newImage, int newHealth);

    void onUpgradeApplied(const QPixmap& newImage, int newHealth);
    void on_fence_clicked();

    void on_cannon_clicked();

signals:
    void moneyChanged(int newMoney);
    void imagehealthChanges(QString type, QPixmap newImage, int newHealth);
public slots:
              // void onFenceUpgraded(const QPixmap& newImage, int newHealth);

private:
    Ui::Shop1 *ui;

};

#endif // SHOP1_H
