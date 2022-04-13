#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <QDialog>

namespace Ui {
class StateMachine;
}

class StateMachine : public QDialog
{
    Q_OBJECT

public:
    explicit StateMachine(QWidget *parent = 0);
    ~StateMachine();

private:
    Ui::StateMachine *ui;
};

#endif // STATEMACHINE_H
