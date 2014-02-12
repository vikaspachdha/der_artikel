#include <QDateTime>
#include <QStringList>
#include "thema_updater.h"

ThemaUpdater_C::ThemaUpdater_C(QObject *parent) :
    QObject(parent),
    _downloading_file_type(NONE)
{
    connect(&_file_downloader, SIGNAL(downloadFinished()), this, SLOT(onFileDownloadFinished()));
}

void ThemaUpdater_C::setRemoteThemaFolderUrl(QUrl url)
{
    if(_remote_thema_folder_url != url) {
        _remote_thema_folder_url = url;
    }
}

void ThemaUpdater_C::checkUpdate()
{
    if(_remote_thema_folder_url.isValid() && _downloading_file_type == NONE) {
        QUrl index_file_url(_remote_thema_folder_url.path() + "/index.csv");
        _downloading_file_type = IS_INDEX;
        _file_downloader.startDownload(index_file_url);
    }
}

void ThemaUpdater_C::onFileDownloadFinished()
{
    QByteArray file_data = _file_downloader.fileData();
    if(_downloading_file_type = IS_INDEX) {
        QHash<QString, QDateTime> parsed_data;
        if(ParseIndexFile(file_data, parsed_data)) {
            foreach (QString key, parsed_data.keys()) {
                qDebug()<<"key - "<<parsed_data[key].toString();
            }
        }
    } else {
        // TODO Thema file.
    }
}

bool ThemaUpdater_C::ParseIndexFile(QByteArray file_data, QHash<QString, QDateTime> &parsed_data)
{
    bool success = false;
    QString data = QString::fromLatin1(file_data);
    if(!data.isEmpty()) {
        // Split text into lines
        QStringList lines = data.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
        // Parse each line
        foreach(QString line, lines) {
            success = true;
            QStringList file_params = line.split(";");
            // Parse file name and update time.
            if(file_params.count() > 1) {
                QString file_name = file_params.at(0);
                QDateTime update_date = QDateTime::fromString(file_params.at(1),Qt::ISODate);
                if(update_date.isValid() && !file_name.isEmpty()) {
                    // Params are parsed, add to structure
                    parsed_data[file_name] = update_date;
                }
            }
        }
    }
    return success;
}

bool ThemaUpdater_C::createOperations(QHash<QString, QDateTime> parsed_data)
{
    QVector<FileOperationData_TP> file_operations;
}

bool ThemaUpdater_C::executeOperations(QVector<ThemaUpdater_C::FileOperationData_TP> _file_operations)
{

}
