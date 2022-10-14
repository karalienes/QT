#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sqlobj = new Sqldataprocessing();
//    sqlobj->createQuery();
    sqlobj->readQuery("PRODUCTS");

}

MainWindow::~MainWindow()
{
    delete ui;
}

