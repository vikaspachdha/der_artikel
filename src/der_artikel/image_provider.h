#ifndef IMAGE_PROVIDER_H
#define IMAGE_PROVIDER_H

#include <QQuickImageProvider>
#include <QHash>
class ImageProvider_C : public QQuickImageProvider
{
public:
    explicit ImageProvider_C();

public:
    void AddImage(QString id, QPixmap pixmap);

public:
    virtual QPixmap	requestPixmap(const QString & id, QSize * size, const QSize & requestedSize);

private:
    QHash<QString, QPixmap> _images;
};

#endif // IMAGE_PROVIDER_H
