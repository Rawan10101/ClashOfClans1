#include "archtower.h"
#include "ui_archtower.h"

ArchTower::ArchTower(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ArchTower)
{
    ui->setupUi(this);
}

ArchTower::~ArchTower()
{
    delete ui;
}
