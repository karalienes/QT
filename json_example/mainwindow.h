#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "libs.h"

using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
struct Book
{
    string name;
    double price;
    Book( string _name, double _price )
    {
        name = _name;
        price = _price;
    }
};
class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void CreateJson(QStringList key, QString root, QString &path, QIODevice::OpenModeFlag device);
    void ReadJson(QString path);

    QString  test = QDir::currentPath()+"/multi2.json";


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
