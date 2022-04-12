#include "mainwindow.h"
#include <QApplication>
// enes karali
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
