#include "mainwindow.h"
#include <QApplication>
#include <dialog.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();


      Dialog d;
      d.show();
    return a.exec();
}
