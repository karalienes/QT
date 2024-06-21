#include "timer.h"
#include "ui_timer.h"

Timer::Timer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Timer)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(MySlot()));

    timer->start(10000);
    this->ui->lineEdit->setText("");
}

Timer::~Timer()
{
    delete ui;
}

void Timer::MySlot(){

    this->ui->lineEdit->setText("Enes");
}
