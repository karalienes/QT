#include "mainwindow.h"

#include <QDebug>
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QFile>
#include <QDateTime>

int main(int argc, char *argv[])
{


    QFile file(QDir::currentPath()+"/deneme");
    QFileInfo file2(QDir::currentPath()+"/deneme");


    QDateTime fileTime = file2.lastModified();
    qDebug()<<fileTime;
    QString fileTimeCnvrt_String = QString::number(fileTime.date().year())+ QString::number(fileTime.date().month())+ QString::number(fileTime.date().day());
    int fileTimeCnvrt_int = fileTimeCnvrt_String.toInt();
    qDebug()<<QString::number(fileTimeCnvrt_int);



    if(!file.open(QIODevice::WriteOnly | QIODevice::Append)){
        qDebug()<<"Hulo dosya acılamadı";
    }


    QTextStream out(&file);

    out<<"deneme";

    out<<"deneme2";

    file.close();


    QString deneme="8;";
    QStringList deneme2 = deneme.split(";");
    qDebug()<<deneme2[0]<<"   +++++  ";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
