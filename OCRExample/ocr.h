#ifndef OCR_H
#define OCR_H

#include <QObject>
#include <QDebug>
#include <QRegularExpression>
#include <QMutex>

#include "rapidfuzz.h"

#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <tesseract/baseapi.h>
//#include "variables.h"
//#include "singleton.h"

using namespace cv;

class Ocr : public QObject
{
    Q_OBJECT
public:
    explicit Ocr(QObject *parent = nullptr);
    ~Ocr();
    const char *database[20] = {"dardanel","dimes","pınar","içim","supradyn",
                           "torku","ülker","ofçay", "selpak","selis",
                           "maylo","filiz","tadım","tamek","lipton",
                           "sensodyne","doğadan","eti","today","jacobs"};

    QMutex mutex;

public:
    void getText(QString &text, Mat &image);
    void setResolution(int ppi);
    void setDefault();
    void showDistance();
    QString outText;

    QString tempText = "";

private:
    tesseract::TessBaseAPI *ocr_api;
    QString removeSpecialChar(QString text);

signals:
    void redText(std::string t);

};

#endif // OCR_H
