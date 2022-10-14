#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    float deneme = 1.5;
    qDebug()<<deneme*1.5f;
}

MainWindow::~MainWindow()
{
    delete ui;
}

