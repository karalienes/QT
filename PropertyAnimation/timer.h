#ifndef TIMER_H
#define TIMER_H

#include <QWidget>
#include <QtCore>

namespace Ui {
class Timer;
}

class Timer : public QWidget
{
    Q_OBJECT

public:
    explicit Timer(QWidget *parent = 0);
    ~Timer();
    QTimer *timer;

private:
    Ui::Timer *ui;

public slots:
    void MySlot();

};

#endif // TIMER_H
