#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <dialogexample1.h>

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

void MainWindow::on_pushButton_clicked()
{

    DialogExample1 *d=new DialogExample1;
    d->show();
}
