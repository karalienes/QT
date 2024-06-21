#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawing.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Drawing_clicked()
{

    Drawing d;
    d.setModal(true);
    d.exec();
}
