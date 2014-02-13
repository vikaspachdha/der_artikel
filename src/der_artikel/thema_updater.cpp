#include <QDateTime>
#include <QStringList>
#include <QFileInfo>

#include "thema_updater.h"

#include "data/thema.h"
#include "thema_loader.h"
#include "settings.h"

ThemaUpdater_C::ThemaUpdater_C(Settings_C &settings, QObject *parent) :
    QObject(parent),
    _settings(settings),
    _downloading_file_type(NONE)
{
    connect(&_file_downloader, SIGNAL(downloadFinished()), this, SLOT(onFileDownloadFinished()));
    connect(&_file_downloader, SIGNAL(downloadAborted()), this, SLOT(onFileDownloadAborted()));
}

void ThemaUpdater_C::checkUpdate()
{
    reset();
    QUrl url = QUrl::fromUserInput(_settings.themaRemotePath() + "/index.csv");
    if(url.isValid() && _downloading_file_type == NONE) {
        _downloading_file_type = IS_INDEX;
        _file_downloader.startDownload(url);
    }
}

void ThemaUpdater_C::onFileDownloadFinished()
{
    QByteArray file_data = _file_downloader.fileData();
    if(_downloading_file_type == IS_INDEX) {
        QHash<QString, QDateTime> parsed_data;
        if(ParseIndexFile(file_data, parsed_data)) {
            foreach (QString key, parsed_data.keys()) {
                qDebug()<<"key - "<<parsed_data[key].toString();
            }
            if(parsed_data.keys().count()> 0) {
                _remote_file_data = parsed_data;
                buildLocalData();
            }
        }
    } else {
        // TODO Thema file.
    }
    _downloading_file_type = NONE;
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

bool ThemaUpdater_C::executeOperations()
{
    bool success = true;
    if(_file_operations.count() >0) {

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
    _downloading_file_type = NONE;
    _remote_file_data.clear();
    _file_operations.clear();
}

void ThemaUpdater_C::onNewThemaLoaded(Thema_C *new_thema)
{
    Q_ASSERT(new_thema);
    new_thema->setParent(this);
    QFileInfo thema_local_file_info(new_thema->filePath());
    if(_remote_file_data.contains(thema_local_file_info.fileName().toLower())) {
        // Replace operation
        FileOperationData_TP file_operation;
        file_operation._operation = REPLACE;
        file_operation._local_file_path = new_thema->filePath();
        file_operation._old_experience = new_thema->ExperiencePoints();
        file_operation._remote_file_url = QUrl::fromUserInput(_settings.themaRemotePath() + "/" + thema_local_file_info.fileName());
        _file_operations.append(file_operation);
        _remote_file_data.remove(thema_local_file_info.fileName().toLower());
    } else {
        // Remove operation
        FileOperationData_TP file_operation;
        file_operation._operation = REMOVE;
        file_operation._local_file_path = new_thema->filePath();
        _file_operations.append(file_operation);
    }
}

void ThemaUpdater_C::onBuildLocalDataFinished()
{
    foreach (QString key, _remote_file_data.keys()) {
        // Add operation
        FileOperationData_TP file_operation;
        file_operation._operation = ADD;
        file_operation._remote_file_url = QUrl::fromUserInput(_settings.themaRemotePath() + "/" + key);
        _file_operations.append(file_operation);
    }

    executeOperations();
}
