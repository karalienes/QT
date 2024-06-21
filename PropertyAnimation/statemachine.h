#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <QDialog>
#include <QStateMachine>
#include <QPropertyAnimation>
#include <QEventTransition>

namespace Ui {
class StateMachine;
}

class StateMachine : public QDialog
{
    Q_OBJECT

public:
    explicit StateMachine(QWidget *parent = 0);
    ~StateMachine();
    void AssignProperty();
    void EventTransition();
    void MachineFunc();
    void PropertyFunc();


private:
    Ui::StateMachine *ui;
    QStateMachine *machine;
    QState *s1;
    QState *s2;
    QEventTransition *t1;
    QEventTransition *t2;
    QEventTransition *t3;
    QEventTransition *t4;

    QPropertyAnimation *p1;

};

#endif // STATEMACHINE_H
