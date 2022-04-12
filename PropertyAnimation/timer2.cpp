#include "timer2.h"
#include "ui_timer2.h"

Timer2::Timer2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Timer2)
{
    ui->setupUi(this);
}

Timer2::~Timer2()
{
    delete ui;
}
