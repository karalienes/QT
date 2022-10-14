#include "mainwindow.h"
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QDebug>

#include <QApplication>

int main(int argc, char *argv[])
{

    QFile file(QDir::currentPath()+"/modifier");

    if(!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)){
        qDebug()<<"File not open!";
        return 0;
    }

    QFileInfo fileInfo(QDir::currentPath()+"/modifier");

    QDateTime fileTime = fileInfo.lastModified();

    qDebug()<<fileTime.toString("yyyyMMddHHmm");
    QString fileTimeCnvrt_String = QString::number(fileTime.date().year())+ QString::number(fileTime.date().month())+ QString::number(fileTime.date().day());
    int fileTimeCnvrt_int = fileTimeCnvrt_String.toInt();


    qDebug()<<fileTimeCnvrt_int <<"::  KARALİ";

    QString as = QDateTime::currentDateTime().toString("yyyyMMddHHmm");
    long int as2 = as.toLong();
    qDebug()<< "As:   "<< as2;

    qDebug()<<QString::number(as2);


    QTextStream out(&file);
    out<<QString::number(as2);
    file.close();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
