#include <QNetworkRequest>
#include <QDebug>
#include "file_downloader.h"
#include "log4qt/log_defines.h"

FileDownloader_C::FileDownloader_C(QObject *parent) :
    QObject(parent),
    _network_reply(0)
{
}

void FileDownloader_C::startDownload(QUrl url)
{
    if(url.isValid()) {
        LOG_INFO("File downloader :: Starting file download URL - " + url.toString());
        stopDownload();
        _file_data.clear();
        _network_reply = _network_manager.get(QNetworkRequest(url));
        connect(_network_reply,SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));
        connect(_network_reply,SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
        connect(_network_reply,SIGNAL(finished()), this, SLOT(onFinished()));
        connect(_network_reply,SIGNAL(readyRead()), this, SLOT(onDataRecieved()));
    }
}

void FileDownloader_C::stopDownload()
{
    if(_network_reply && !_network_reply->isFinished()) {
        LOG_INFO("File downloader :: Stopping file download");
        _network_reply->abort();
        _network_reply->deleteLater();
        _network_reply = 0;
        emit downloadAborted();
    }
}

void FileDownloader_C::onDownloadProgress(qint64 bytes_recieved, qint64 total_bytes)
{
    LOG_INFO(QString("File downloader :: Download progress %1 bytes %2").
             arg(bytes_recieved).
             arg((bytes_recieved)/total_bytes));
    emit downloadProgress(double(bytes_recieved)/total_bytes);
}

void FileDownloader_C::onError(QNetworkReply::NetworkError errorCode)
{
    LOG_ERROR(QString("File downloader :: File download error. Error code:: %1").arg(errorCode));
    emit downloadAborted();
}

void FileDownloader_C::onFinished()
{
    LOG_INFO("File downloader :: File download finished");
    _file_data.append(_network_reply->readAll());
    _network_reply->deleteLater();
    _network_reply = 0;
    emit downloadFinished();
}

void FileDownloader_C::onDataRecieved()
{
    LOG_INFO("File downloader :: data received");
    _file_data.append(_network_reply->readAll());
}
