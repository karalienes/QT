#include "animation.h"
#include "ui_animation.h"

#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

Animation::Animation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Animation)
{
    ui->setupUi(this);
    this->PushButtonSet();
}

Animation::~Animation()
{
    delete ui;
}

void Animation::PushButtonSet(){


    animation =new QPropertyAnimation(ui->pushButton, "geometry");
    animation->setDuration(3000);
    animation->setStartValue(ui->pushButton->geometry());
    animation->setEndValue(QRect(50,200,100,50));


    animation2 = new QPropertyAnimation(ui->pushButton_2, "geometry");
    animation2->setDuration(3000);
    animation2->setStartValue(ui->pushButton_2->geometry());
    animation2->setEndValue(QRect(150,200,100,50));


    animation3 = new QPropertyAnimation(ui->pushButton_3, "geometry");
    animation3->setDuration(3000);
    animation3->setStartValue(ui->pushButton_3->geometry());
    animation3->setEndValue(QRect(250,200,100,50));


    this->CurveSet();

}

void Animation::CurveSet()
{

    QEasingCurve curve;
    curve.setType(QEasingCurve::OutBounce);
    curve.setAmplitude(1.00);
    curve.setOvershoot(1.70);
    curve.setPeriod(0.75);

    animation->setEasingCurve(curve);
    animation2->setEasingCurve(curve);
    animation3->setEasingCurve(curve);

    this->seqGroupSet();

}

void Animation::GroupSet()
{

    group = new QParallelAnimationGroup;
    group->addAnimation(animation);
    group->addAnimation(animation2);
    group->addAnimation(animation3);

    group->start();


}

void Animation::seqGroupSet()
{

    seqgroup = new QSequentialAnimationGroup;
    seqgroup->addAnimation(animation3);
    seqgroup->addAnimation(animation);
    seqgroup->addAnimation(animation2);

    seqgroup->start();

}
