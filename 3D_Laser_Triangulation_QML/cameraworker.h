#ifndef CAMERA_WORKER_H
#define CAMERA_WORKER_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QImage>
#include <QDebug>

class CameraWorker : public QObject {
    Q_OBJECT

public:
    explicit CameraWorker(int cameraIndex, QObject *parent = nullptr);
    ~CameraWorker();
    Q_PROPERTY(QImage frame READ frame NOTIFY frameReady)

    QImage frame() const { return m_frame; }


signals:
    void frameReady(const QImage &frame);

public slots:
     Q_INVOKABLE void process();

private:
    QImage cvMatToQImage(const cv::Mat &mat);
    QImage m_frame;
    int cameraIndex;
    cv::VideoCapture cap;
    bool running;
};

#endif // CAMERA_WORKER_H
