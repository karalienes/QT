#include "multianimation.h"
#include "ui_multianimation.h"

MultiAnimation::MultiAnimation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MultiAnimation)
{
    ui->setupUi(this);
    this->PushButtonSet();
}

MultiAnimation::~MultiAnimation()
{
    delete ui;

}


void MultiAnimation::PushButtonSet()
{

    animation = new QPropertyAnimation(ui->pushButton, "geometry");
    animation->setDuration(3000);
    animation->setStartValue(ui->pushButton->geometry());
    animation->setEndValue(QRect(50,50,100,50));


    animation2 = new QPropertyAnimation(ui->pushButton_2, "geometry");
    animation2->setDuration(3000);
    animation2->setStartValue(ui->pushButton_2->geometry());
    animation2->setEndValue(QRect(150,50,100,50));


    animation3 = new QPropertyAnimation(ui->pushButton_3, "geometry");
    animation3->setDuration(3000);
    animation3->setStartValue(ui->pushButton_3->geometry());
    animation3->setEndValue(QRect(250,50,100,50));

    animation4 = new QPropertyAnimation(ui->pushButton_4, "geometry");
    animation4->setDuration(3000);
    animation4->setStartValue(ui->pushButton_4->geometry());
    animation4->setEndValue(QRect(50,200,100,50));


    animation5 = new QPropertyAnimation(ui->pushButton_5, "geometry");
    animation5->setDuration(3000);
    animation5->setStartValue(ui->pushButton_5->geometry());
    animation5->setEndValue(QRect(150,200,100,50));

    animation6 = new QPropertyAnimation(ui->pushButton_6, "geometry");
    animation6->setDuration(3000);
    animation6->setStartValue(ui->pushButton_6->geometry());
    animation6->setEndValue(QRect(250,200,100,50));

    this->CurveSet();

}


void MultiAnimation::CurveSet()
{
    QEasingCurve curve;
    curve.setType(QEasingCurve::OutBounce);
    curve.setAmplitude(1.00);
    curve.setOvershoot(1.70);
    curve.setPeriod(0.30);


    animation->setEasingCurve(curve);
    animation2->setEasingCurve(curve);
    animation3->setEasingCurve(curve);
    animation4->setEasingCurve(curve);
    animation5->setEasingCurve(curve);
    animation6->setEasingCurve(curve);

    this->GroupSet();

}

void MultiAnimation::GroupSet()
{

    group = new QParallelAnimationGroup;
    group->addAnimation(animation);
    group->addAnimation(animation2);
    group->addAnimation(animation3);

    group2 = new QParallelAnimationGroup;
    group2->addAnimation(animation4);
    group2->addAnimation(animation5);
    group2->addAnimation(animation6);

    this->seqGroupSet();

}


void MultiAnimation::seqGroupSet()
{
    seqgroup = new QSequentialAnimationGroup;
    seqgroup->addAnimation(group);
    seqgroup->addAnimation(group2);

    seqgroup->start();
}

