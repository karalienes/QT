#include "statemachine.h"
#include "ui_statemachine.h"

StateMachine::StateMachine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StateMachine)
{
    ui->setupUi(this);
}

StateMachine::~StateMachine()
{
    delete ui;
}


void StateMachine::AssignProperty()
{
    s1= new QState();

    s1->assignProperty(ui->StateLabel, "text"," Current state : 1");
    s1->assignProperty(ui->pushButton, "geometry", QRect(50,200,100,50));

    s2 = new QState();

    s2->assignProperty(ui->StateLabel, "text", "Current state: 2");
    s2->assignProperty(ui->pushButton, "geometry", QRect(200,50,140,100));

    this->EventTransition();

}

void StateMachine::EventTransition()
{
    t1 = new QEventTransition(ui->ChangeState, QEvent::MouseButtonPress);
    t1->setTargetState(s2);
    t1->addAnimation(new QPropertyAnimation(ui->pushButton, "geometry"));
    s1->addTransition(t1);


    t2= new QEventTransition(ui->ChangeState, QEvent::MouseButtonPress);
    t2->setTargetState(s1);
    t1->addAnimation(new QPropertyAnimation(ui->pushButton, "geometry"));
    s2->addTransition(t2);

    this->MachineFunc();

}

void StateMachine::MachineFunc()
{
    machine = new QStateMachine(this);

    machine->addState(s1);
    machine->addState(s2);

    machine->setInitialState(s1);
    machine->start();

    this->PropertyFunc();
}

void StateMachine::PropertyFunc()
{

    p1 = new QPropertyAnimation(ui->pushButton, "geometry");
    p1->setEasingCurve(QEasingCurve::OutBounce);

    t3= new QEventTransition(ui->ChangeState , QEvent::MouseButtonPress);
    t3->setTargetState(s2);
    t3->addAnimation(p1);
    s1->addTransition(t3);


    t4=new QEventTransition(ui->ChangeState, QEvent::MouseButtonPress);
    t4->setTargetState(s1);
    t4->addAnimation(p1);
    s2->addTransition(t4);

}
