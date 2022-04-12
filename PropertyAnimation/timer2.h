#ifndef TIMER2_H
#define TIMER2_H

#include <QDialog>

namespace Ui {
class Timer2;
}

class Timer2 : public QDialog
{
    Q_OBJECT

public:
    explicit Timer2(QWidget *parent = 0);
    ~Timer2();

private:
    Ui::Timer2 *ui;
};

#endif // TIMER2_H
