#include "cameraworker.h"
#include <qdebug.h>
#include <qthread.h>

CameraWorker::CameraWorker(int cameraIndex, QObject *parent)
    : QObject(parent), cameraIndex(cameraIndex), running(true) {

    // OpenCV VideoCapture ile MJPEG akışını başlatın
    QString filename = "v4l2src device=/dev/video"+ QString::number(cameraIndex)+ " ! image/jpeg, width=1920, height=1080 ! jpegdec ! videoconvert ! appsink";
    cap = cv::VideoCapture(filename.toStdString(), cv::CAP_GSTREAMER);

    if (!cap.isOpened()) {
        qWarning("Kamera açılamadı!");
        return;
    }
    // MJPEG formatını ve çözünürlüğü ayarla
    // cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
    // cap.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
    // cap.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);



    // Çözünürlük kontrolü
    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    std::cout << "Kamera çözünürlüğü: " << width << "x" << height << std::endl;
}

CameraWorker::~CameraWorker() {
    running = false;
    cap.release();
}

void CameraWorker::process() {
    cv::Mat frame;
    while (running) {
        if (!cap.read(frame) || frame.empty()) {
            qWarning("Kare okunamadı veya boş!");
            QThread::msleep(100);
            continue;
        }

        qDebug() << "Frame boyutu: " << frame.cols << "x" << frame.rows;
        qDebug() << "Frame türü: " << frame.type();

        QImage qImage = cvMatToQImage(frame);
        emit frameReady(qImage);
    }
}

QImage CameraWorker::cvMatToQImage(const cv::Mat &mat) {
    qDebug() << "cvMatToQImage çağrıldı. Mat type:" << mat.type();
    if (mat.empty()) {
        qWarning("cvMatToQImage: Mat boş!");
        return QImage();
    }

    if (mat.type() == CV_8UC3) {
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888).rgbSwapped();
    } else if (mat.type() == CV_8UC1) {
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
    } else {
        qWarning("cvMatToQImage: Desteklenmeyen format!");
        return QImage();
    }
}
