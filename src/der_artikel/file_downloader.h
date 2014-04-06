#ifndef FILE_DOWNLOADER_H
#define FILE_DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QDataStream>
#include <QTextStream>
#include<QNetworkReply>


class FileDownloader_C : public QObject
{
    Q_OBJECT
public:
    explicit FileDownloader_C(QObject *parent = 0);

public:
    QByteArray fileData() const {return _file_data; }

public:
    void startDownload(QUrl url);
    void stopDownload();

private slots:
    void onDownloadProgress(qint64 bytes_recieved, qint64 total_bytes);
    void onError(QNetworkReply::NetworkError errorCode);
    void onFinished();
    void onDataRecieved();

signals:
    void downloadProgress(double progress);
    void downloadFinished();
    void downloadAborted();

private:
    QNetworkAccessManager _network_manager;
    QNetworkReply* _network_reply;
    QByteArray _file_data;
    QTextStream* _data_steam;
};

#endif // FILE_DOWNLOADER_H
