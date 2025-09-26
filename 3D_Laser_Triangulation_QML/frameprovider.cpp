#include "frameprovider.h"

FrameProvider::FrameProvider()
    : QQuickImageProvider(QQuickImageProvider::Image) {}

QImage FrameProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize) {
    Q_UNUSED(id);
    Q_UNUSED(requestedSize);

    if (size) {
        *size = currentFrame.size();
    }

    return currentFrame;
}

void FrameProvider::updateFrame(const QImage &frame) {
    currentFrame = frame;
}
