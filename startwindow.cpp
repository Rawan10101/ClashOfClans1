#include "startwindow.h"
#include "ui_startwindow.h"
#include <QLabel>
#include <QPalette>
#include <QProgressBar>
#include <QTimer>
#include "startwindow.h"
startwindow::startwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::startwindow)
{
    ui->setupUi(this);

    QPixmap backgroundImage(":/images/startbg.jpg");
    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(backgroundImage);
    backgroundLabel->lower();
    backgroundLabel->setGeometry(0, 0, width(), height());


    ui->progressBar->setGeometry(98, 250, 200, 25);
    ui->progressBar->setStyleSheet("QProgressBar { border: 2px solid orange; background-color: black; text-align: center; }"
                                   "QProgressBar::chunk { background-color: orange; }"
                                   "QProgressBar::chunk::text { color: transparent; }");
    ui->progressBar->setRange(0, 100);


    QLabel *loadingLabel = new QLabel("LOADING...", this);
    int progressBarY = ui->progressBar->y();
    int progressBarX = ui->progressBar->x();
    int progressBarHeight = ui->progressBar->height();
    loadingLabel->setGeometry(progressBarX, progressBarY - progressBarHeight - 10, 200, 25);
    loadingLabel->setAlignment(Qt::AlignCenter);


    QFont font = loadingLabel->font();
    font.setBold(true);
    font.setPointSize(14);
    loadingLabel->setFont(font);

    loadingLabel->setStyleSheet("color: rgb(255, 165, 0);");
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &startwindow::updateProgressBar);
    timer->start(180);

    name = new QLabel(this);
    name->setText("Save The Cake!");
    name->setGeometry(60, 90, 300, 70);
    name->setAlignment(Qt::AlignCenter);

    QFont font1 = name->font();
    font1.setPointSize(24);
    name->setFont(font1);

    QPalette namePalette = name->palette();
    namePalette.setColor(QPalette::WindowText, QColor(255, 165, 0));
    name->setPalette(namePalette);

    name->show();
}


startwindow::~startwindow()
{
    delete ui;
}

void startwindow::updateProgressBar()
{
    static int value = 0;

    value += 10;
    ui->progressBar->setValue(value);

    if (value >= 100) {
        sender()->deleteLater();
        ui->progressBar->hide();

        Game* game = new Game();
        game->show();
        this->hide();
    }
}


