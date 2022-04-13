#include "animation.h"
#include "ui_animation.h"

Animation::Animation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Animation)
{
    ui->setupUi(this);
}

Animation::~Animation()
{
    delete ui;
}
