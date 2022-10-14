#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>

#include <string>
#include <stdlib.h>
#include <iostream>

#include "gallo.h"
#include "soros.h"
#include "yun.h"


#include <iostream>
#include <algorithm>
#include <vector>
#include <zbar.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/photo.hpp>

using namespace std;
using namespace cv;
using namespace zbar;

typedef struct
{
  string type;
  string data;
  vector <Point> location;
}decodedObject;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
//    enum ZBAR_DATA{
//        ZBAR_NONE,
//        ZBAR_PARTIAL,
//        ZBAR_EAN8,
//        ZBAR_UPCE,
//        ZBAR_ISBN10,
//        ZBAR_UPCA,
//        ZBAR_EAN13,
//        ZBAR_ISBN13,
//        ZBAR_I25,
//        ZBAR_CODE39,
//        ZBAR_PDF417,
//        ZBAR_QRCODE,
//        ZBAR_CODE128,
//        ZBAR_SYMBOL,
//        ZBAR_ADDON2,
//        ZBAR_ADDON5,
//        ZBAR_ADDON
//    };
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void decode(Mat &im, vector<decodedObject>&decodedObjects);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
