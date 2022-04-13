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
