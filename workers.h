#ifndef WORKERS_H
#define WORKERS_H

#include <QDialog>

namespace Ui {
class Workers;
}

class Workers : public QDialog
{
    Q_OBJECT

public:
    explicit Workers(QWidget *parent = nullptr);
    ~Workers();

private:
    Ui::Workers *ui;
};

#endif // WORKERS_H
