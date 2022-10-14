#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imgprocess = new ImgPreProcessing();
//    imgprocess->Binarization();
//    imgprocess->skewCorrention();
}

MainWindow::~MainWindow()
{
    delete ui;
}

