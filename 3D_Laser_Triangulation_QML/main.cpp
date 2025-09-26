#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "cameraworker.h"
#include "frameprovider.h"
#include "imageprovider.h"
#include <QThread>


int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;



    CameraWorker * cameraWorker = new CameraWorker(0);
    QThread * cameraThread = new QThread();
    cameraWorker->moveToThread(cameraThread);
    QObject::connect(cameraThread, &QThread::started, cameraWorker, &CameraWorker::process);

    cameraThread->start();
    ImageProvider *imageProvider = new ImageProvider();

    engine.rootContext()->setContextProperty("CameraWorker",cameraWorker);
    engine.rootContext()->setContextProperty("ImageProvider",imageProvider);

    engine.addImageProvider("live",imageProvider);

    QObject::connect(cameraWorker, &CameraWorker::frameReady, imageProvider, &ImageProvider::updateFrame);

    engine.load(QUrl(QStringLiteral("qrc:/MyApp/qml/Main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }


    return app.exec();
}
