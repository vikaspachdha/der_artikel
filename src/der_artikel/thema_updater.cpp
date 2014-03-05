#include <QDateTime>
#include <QStringList>
#include <QFileInfo>
#include <QDir>

#include "thema_updater.h"

#include "data/thema.h"
#include "thema_loader.h"
#include "manager.h"
#include "settings.h"
#include "common.h"
#include "algo/thema_add_operation.h"
#include "algo/thema_replace_operation.h"
#include "algo/thema_delete_operation.h"

ThemaUpdater_C::ThemaUpdater_C(Manager_C &manager, QObject *parent) :
    QObject(parent),
    _manager(manager)
{
    connect(&_file_downloader, SIGNAL(downloadFinished()), this, SLOT(onFileDownloadFinished()));
    connect(&_file_downloader, SIGNAL(downloadAborted()), this, SLOT(onFileDownloadAborted()));
}

void ThemaUpdater_C::checkUpdate()
{
    reset();
    QUrl url = QUrl::fromUserInput(_manager.GetSettings()->themaRemotePath() + "/index.csv");
    if(url.isValid()) {
        _file_downloader.startDownload(url);
    }
}

void ThemaUpdater_C::onFileDownloadFinished()
{
    QByteArray file_data = _file_downloader.fileData();
    QHash<QString, QDateTime> parsed_data;
    if(ParseIndexFile(file_data, parsed_data)) {
//        foreach (QString key, parsed_data.keys()) {
//            qDebug()<<"key - "<<parsed_data[key].toString();
//        }
        if(parsed_data.keys().count()> 0) {
            _remote_file_data = parsed_data;
            buildLocalData();
        }
    }
}

void ThemaUpdater_C::onFileDownloadAborted()
{
    emit updateResponse(UPDATE_ERROR);
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
                QString file_name = file_params.at(0).toLower();
                QString update_time_str = file_params.at(1);
                bool ok = false;
                qint64 msecs = update_time_str.toLongLong(&ok);
                QDateTime update_date = QDateTime::fromMSecsSinceEpoch(msecs);
                if(update_date.isValid() && !file_name.isEmpty()) {
                    // Params are parsed, add to structure
                    parsed_data[file_name] = update_date;
                }
            }
        }
    }
    return success;
}

bool ThemaUpdater_C::executeOperations()
{
    bool success = true;
    if(_file_operations.count() >0) {
        foreach (ThemaFileOperation_I* operation, _file_operations) {
            operation->execute();
        }
        _manager.LoadDefaultThemas();
        emit updateResponse(UPDATE_FINISHED);
    } else {
        emit updateResponse(UPDATE_NOT_AVAILABLE);
    }
    return success;
}

void ThemaUpdater_C::buildLocalData()
{
    // thema_loader shall be deleted automatically.
    ThemaLoader_C* thema_loader = new ThemaLoader_C(this);
    connect(thema_loader, SIGNAL(ThemaLoaded(Thema_C*)), this, SLOT(onNewThemaLoaded(Thema_C*)) );
    connect(thema_loader,SIGNAL(finishedLoading()),this, SLOT(onBuildLocalDataFinished()) );
    thema_loader->StartLoading();
}

void ThemaUpdater_C::reset()
{
    _remote_file_data.clear();
    _file_operations.clear();
}

void ThemaUpdater_C::onNewThemaLoaded(Thema_C *thema)
{
    Q_ASSERT(thema);
    thema->setParent(this);
    QFileInfo thema_local_file_info(thema->filePath());
    if(_remote_file_data.contains(thema_local_file_info.fileName().toLower())) {
        //qDebug()<<thema_local_file_info.fileName().toLower()<<" "<<_remote_file_data[thema_local_file_info.fileName().toLower()].toString(Qt::TextDate)<<" "<<thema->LastUpdated().toString(Qt::TextDate);
        if(_remote_file_data[thema_local_file_info.fileName().toLower()] > thema->LastUpdated()) {
            // Replace operation
            QString local_file_path = thema->filePath();
            QUrl remote_file_url = QUrl::fromUserInput(_manager.GetSettings()->themaRemotePath() + "/" + thema_local_file_info.fileName());
            ThemaFileOperation_I* operation = new ThemaReplaceOperation_C(local_file_path,
                                                                          remote_file_url,
                                                                          thema->ExperiencePoints());
            _file_operations.append(operation);
        }
        _remote_file_data.remove(thema_local_file_info.fileName().toLower());
    } else {
        // Remove operation
        ThemaFileOperation_I* operation = new ThemaDeleteOperation_C(thema->filePath());
        _file_operations.append(operation);
    }
}

void ThemaUpdater_C::onBuildLocalDataFinished()
{
    foreach (QString key, _remote_file_data.keys()) {
        // Add operation
        QString local_file_path = ARTIKEL::GetResourcePath("thema") + QDir::separator()+ key;
        QUrl remote_file_url = QUrl::fromUserInput(_manager.GetSettings()->themaRemotePath() + "/" + key);
                ThemaFileOperation_I* operation = new ThemaAddOperation_C(local_file_path, remote_file_url);
        _file_operations.append(operation);
    }

    executeOperations();
}
