#ifndef TROOP_H
#define TROOP_H

#include <QDialog>

namespace Ui {
class Troop;
}

class Troop : public QDialog
{
    Q_OBJECT

public:
    explicit Troop(QWidget *parent = nullptr);
    ~Troop();

private:
    Ui::Troop *ui;
};

#endif // TROOP_H
