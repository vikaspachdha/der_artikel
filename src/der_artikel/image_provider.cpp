#include "image_provider.h"

ImageProvider_C::ImageProvider_C() :
    QQuickImageProvider(QQuickImageProvider::Pixmap)
{
}

void ImageProvider_C::AddImage(QString id, QPixmap pixmap)
{
    _images[id] = pixmap;
}

QPixmap ImageProvider_C::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(size);
    Q_UNUSED(requestedSize);
    return _images[id];
}
