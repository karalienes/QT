#include "timer2.h"
#include "ui_timer2.h"

Timer2::Timer2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Timer2)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(MySlot()));

    timer->start(10000);
}

Timer2::~Timer2()
{
    delete ui;
}

void Timer2::MySlot(){

    this->ui->lineEdit->setText("Enes");
}
