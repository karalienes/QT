#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QDebug>
#include <QObject>
#include <QQuickImageProvider>
#include <QMutex>

class ImageProvider :public QQuickImageProvider
{
    Q_OBJECT

public:
    explicit ImageProvider(QObject *parent=nullptr);
    ~ImageProvider();

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

public slots:
    void updateFrame(const QImage &image);

signals:
    void imageChanged();

private:
    QImage image;
};


#endif // IMAGEPROVIDER_H
