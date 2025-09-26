#ifndef FRAMEPROVIDER_H
#define FRAMEPROVIDER_H

#include <QQuickImageProvider>
#include <QImage>

class FrameProvider : public QQuickImageProvider {
public:
    FrameProvider();

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
    void updateFrame(const QImage &frame);

private:
    QImage currentFrame;
};

#endif // FRAMEPROVIDER_H
