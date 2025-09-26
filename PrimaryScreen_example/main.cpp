#include "mainwindow.h"

#include <QApplication>
#include <QScreen>
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Ekran çözünürlüğünü al
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    int b = '?';
    qDebug()<< b;

    MainWindow w;
    w.resize(screenWidth, screenHeight);
    w.show();
    return a.exec();
}
