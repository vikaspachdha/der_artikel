#ifndef IMAGE_PROVIDER_H
#define IMAGE_PROVIDER_H

#include <QQuickImageProvider>
#include <QHash>
/**
 * @brief
 *
 */
class ImageProvider_C : public QQuickImageProvider
{
public:
    /**
     * @brief
     *
     */
    explicit ImageProvider_C();

public:
    /**
     * @brief
     *
     * @param id
     * @param pixmap
     */
    void AddImage(QString id, QPixmap pixmap);

public:
    /**
     * @brief
     *
     * @param id
     * @param size
     * @param requestedSize
     * @return QPixmap
     */
    virtual QPixmap	requestPixmap(const QString & id, QSize * size, const QSize & requestedSize);

private:
    QHash<QString, QPixmap> _images; /**< TODO */
};

#endif // IMAGE_PROVIDER_H
