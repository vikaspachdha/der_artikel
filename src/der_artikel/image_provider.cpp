#include "image_provider.h"
#include "log4qt/log_defines.h"
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
    LOG_INFO("Image provider :: Image added for id - "+id);
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
    LOG_INFO("Image provider :: Image request for id - "+id);
    return _images[id];
}
