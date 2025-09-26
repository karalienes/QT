#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    zlibClass_obj = new zlibClass();
    QStringList filesToZip;
    filesToZip << "/home/karali/Music/Test/zipTest/offSet" << "/home/karali/Music/Test/zipTest/test4.xml";
    zlibClass_obj->zipFiles("/home/karali/Music/Test/zipTest/test.zip", filesToZip);
    zlibClass_obj->unzipFiles("/home/karali/Music/Test/unZipTest/test.zip","/home/karali/Music/Test/unZipTest");
}

MainWindow::~MainWindow()
{
    delete ui;
}
