#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString as = QDateTime::currentDateTime().toString("dd-MMM-yy-hh-mm-ss-zzz000000A");
    qDebug()<<as;
    qDebug()<<"karali";
}

MainWindow::~MainWindow()
{
    delete ui;
}

