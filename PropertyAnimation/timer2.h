#ifndef TIMER2_H
#define TIMER2_H

#include <QDialog>
#include <QtCore>

namespace Ui {
class Timer2;
}

class Timer2 : public QDialog
{
    Q_OBJECT

public:
    explicit Timer2(QWidget *parent = 0);
    ~Timer2();
    QTimer *timer;

private:
    Ui::Timer2 *ui;

public slots:
    void MySlot();
};

#endif // TIMER2_H
