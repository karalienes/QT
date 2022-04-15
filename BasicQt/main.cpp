#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include "yourage.h"
#include "dialogexample1.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    //HTML olarakda yazılabilmektedir.
    QLabel *label = new QLabel("<h2><i>Hello </i> <font color=red>Qt!</font></h2>");
    label->show();

    QPushButton *pushbutton = new QPushButton("Quit");


    // Bu durum connect olayı projeyi kapatmak için vardır.
    QObject::connect(pushbutton,SIGNAL(clicked()), &a,SLOT(quit()));

    pushbutton->show();


    YourAge y;
    y.YourAgeFunc();






    return a.exec();
}
