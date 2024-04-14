#ifndef TROOP_H
#define TROOP_H

#include <QDialog>
#include <QObject>

namespace Ui {
class Troop;
}

class Troop : public QObject
{
    Q_OBJECT

public:
    explicit Troop(QWidget *parent = nullptr);
    ~Troop();

private:
    Ui::Troop *ui;
};

#endif // TROOP_H
