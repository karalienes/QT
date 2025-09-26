#include "imageprovider.h"
#include <qmutex.h>

QImage d_frame;

ImageProvider ::ImageProvider(QObject *parent) : QQuickImageProvider(QQuickImageProvider::Image)
{
    image = QImage(200,200,QImage::Format_RGB32);
    image.fill(QColor("black"));
}

ImageProvider::~ImageProvider()
{

}

void ImageProvider::updateFrame(const QImage &image)
{
    if(!image.isNull() && this->image != image)
    {
        this->image = image;
        emit imageChanged();
    }
}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id);

    if(size)
    {
        *size = image.size();
    }

    if(requestedSize.width()>0 && requestedSize.height()>0)
    {
        image = image.scaled(requestedSize.width(),requestedSize.height(),Qt::KeepAspectRatio);
    }

    return image;
}
