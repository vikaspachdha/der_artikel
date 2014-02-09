#include "image_provider.h"

/*!
 \brief

*/
ImageProvider_C::ImageProvider_C() :
    QQuickImageProvider(QQuickImageProvider::Pixmap)
{
}

/*!
 \brief

 \param id
 \param pixmap
*/
void ImageProvider_C::AddImage(QString id, QPixmap pixmap)
{
    _images[id] = pixmap;
}

/*!
 \brief

 \param id
 \param size
 \param requestedSize
 \return QPixmap
*/
QPixmap ImageProvider_C::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(size);
    Q_UNUSED(requestedSize);
    return _images[id];
}
