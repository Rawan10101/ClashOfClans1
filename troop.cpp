#include "troop.h"
#include "health.h"

Troop::Troop(QWidget *parent)
    : QDialog(parent)

{

}

Troop::~Troop()
{
    delete ui;
}
