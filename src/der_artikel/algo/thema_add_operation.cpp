#include <QFile>
#include <QDataStream>
#include "thema_add_operation.h"

ThemaAddOperation_C::ThemaAddOperation_C(QString local_file_path, QUrl remote_file_url):
    QObject(0),
    _local_file_path(local_file_path),
    _remote_file_url(remote_file_url)
{
    connect(&_file_downloader, SIGNAL(downloadFinished()), this, SLOT(onFileDownloadFinished()));
    connect(&_file_downloader, SIGNAL(downloadAborted()), this, SLOT(onFileDownloadAborted()));
}

bool ThemaAddOperation_C::execute()
{
    bool success = true;
    if(_remote_file_url.isValid()) {
        _file_downloader.startDownload(_remote_file_url);
        success = _event_loop.exec() == 0 ?true:false ;
    } else {
        success = false;
    }
    return success;
}

void ThemaAddOperation_C::onFileDownloadFinished()
{
    QByteArray file_data = _file_downloader.fileData();
    int exit_code = -1;
    QFile file(_local_file_path);
    if (file.open(QFile::WriteOnly)) {
        QDataStream out(&file);
        out<<file_data;
        file.close();
        exit_code = 0;
    }
    _event_loop.exit(exit_code);
}

void ThemaAddOperation_C::onFileDownloadAborted()
{
    _event_loop.exit(-1);
}



