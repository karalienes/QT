#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>
#include "timer2.h"
#include "animation.h"
#include "multianimation.h"
#include "statemachine.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->propertyAnimation();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::propertyAnimation()
{

    QPropertyAnimation *animation = new QPropertyAnimation(ui->pushButton, "geometry");
    animation->setDuration(10000);
    animation->setStartValue(ui->pushButton->geometry());
    //QRect(int x, int y, int width, int height)
    animation->setEndValue(QRect(200,200,100,50));

    //ın this example, we will learn how to make our animation more interesting by utilizing easing curves.
    QEasingCurve curve;
    curve.setType(QEasingCurve::OutBounce);


    // Genlik ayarlaması yapmaktadır.
    curve.setAmplitude(1.00);
    // Aşmayı ayarlamaktadır.
    curve.setOvershoot(1.70);
    //Küçük bir periyot değeri ayarlamak, eğrinin yüksek frekansını verecektir.
    //Büyük bir periyot ona küçük bir frekans verecektir.
    curve.setPeriod(0.30);

    //animation->setEasingCurve(curve);
    //This property holds the loop count of the animation
    //This property describes the loop count of the animation as an integer.
    // default -> 1;
    animation->setLoopCount(2);
    animation->start();
}

void MainWindow::on_Timer_clicked()
{
   Timer2 t1;
   t1.setModal(true);
   t1.exec();

}

void MainWindow::on_pushButton_2_clicked()
{
    Animation a;
    a.setModal(true);
    a.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    MultiAnimation m;
    m.setModal(true);
    m.exec();
}

void MainWindow::on_StatePush_clicked()
{
    StateMachine s;
    s.setModal(true);
    s.exec();
}
