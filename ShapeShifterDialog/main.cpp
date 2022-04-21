#include "mainwindow.h"
#include <QApplication>
#include <extensiondialog.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    ExtensionDialog e;
    e.setColumnRange('C','F');
    e.show();

    return a.exec();
}
