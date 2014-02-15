#include <QFile>
#include <QDataStream>
#include <thema_loader.h>
#include "thema_replace_operation.h"
#include "data/thema.h"

ThemaReplaceOperation_C::ThemaReplaceOperation_C(QString local_file_path, QUrl remote_file_url, int old_experience):
    QObject(0),
    _local_file_path(local_file_path),
    _remote_file_url(remote_file_url),
    _old_experience(old_experience)
{
    connect(&_file_downloader, SIGNAL(downloadFinished()), this, SLOT(onFileDownloadFinished()));
    connect(&_file_downloader, SIGNAL(downloadAborted()), this, SLOT(onFileDownloadAborted()));
}

bool ThemaReplaceOperation_C::execute()
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

void ThemaReplaceOperation_C::onFileDownloadFinished()
{
    QByteArray file_data = _file_downloader.fileData();
    int exit_code = -1;
    QFile file(_local_file_path);
    if (file.open(QFile::WriteOnly)) {
        QDataStream out(&file);
        out<<file_data;
        file.close();
        ThemaLoader_C thema_loader;
        Thema_C* thema = thema_loader.LoadThema(_local_file_path);
        if(thema) {
            // reset the old experience points
            thema->AddExperiencePoints(_old_experience);
            thema->Save();
            delete thema;
            exit_code = 0;
        } else {
            // Something went bad. Thema not replaced
            QFile::remove(_local_file_path);
        }
    }
    _event_loop.exit(exit_code);
}

void ThemaReplaceOperation_C::onFileDownloadAborted()
{
    _event_loop.exit(-1);
}


