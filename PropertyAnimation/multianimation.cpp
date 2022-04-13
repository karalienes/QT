#include "multianimation.h"
#include "ui_multianimation.h"

MultiAnimation::MultiAnimation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MultiAnimation)
{
    ui->setupUi(this);
}

MultiAnimation::~MultiAnimation()
{
    delete ui;
}
