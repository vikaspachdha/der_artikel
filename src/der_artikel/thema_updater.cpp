//******************************************************************************
/*! \file thema_updater.cpp Implementation of \ref ThemaUpdater_C
 *
 *  \author Vikas Pachdha
 *
 *  \copyright Copyright (C) 2014 Vikas Pachdha, Mohita Gandotra.
 * Contact: http://www.vikaspachdha.com
 *
 * This file is part of the application der_artikel.
 *
 *  \copyright GNU Lesser General Public License Usage
 * This file may be used under the terms of the GNU Lesser
 * General Public License version 2.1 as published by the Free Software
 * Foundation and appearing in the file LICENSE.LGPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU Lesser General Public License version 2.1 requirements
 * will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 *
 *  \copyright GNU General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 *
 ******************************************************************************/

// System includes
#include <QDateTime>
#include <QDir>
#include <QFileInfo>
#include <QStringList>

// Interface for this file
#include "thema_updater.h"

// Framework and lib includes
#include "data/common.h"
#include "data/thema.h"
#include "data/thema_loader.h"
#include "log4qt/log_defines.h"

// Project includes
#include "manager.h"
#include "settings.h"
#include "algo/thema_add_operation.h"
#include "algo/thema_replace_operation.h"
#include "algo/thema_delete_operation.h"

//******************************************************************************
/*! \brief Constructor
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] manager : \ref Manager_C class reference.
 *  \param[out] parent : Parent instance
 ******************************************************************************/
ThemaUpdater_C::ThemaUpdater_C(Manager_C &manager, QObject *parent) :
    QObject(parent),
    _manager(manager),
    _progress(0.0),
    _state(INVALID)
{
    connect(&_file_downloader, SIGNAL(downloadFinished()), this, SLOT(onIndexFileDownloadFinished()));
    connect(&_file_downloader, SIGNAL(downloadAborted()), this, SLOT(onFileDownloadAborted()));
}

//******************************************************************************
/*! \brief Initiates checking if thema files update is available or not.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] remote_path : Remote path of the directory from where the thema
 *  shall be updated. Default remote path shall be used in case of empty input.
 ******************************************************************************/
void ThemaUpdater_C::checkUpdate(QString remote_path)
{
    _progress = 0.0;
    setUpdateState(UPDATE_STARTED);
    emit updateProgress(tr("Checking for thema update."), _progress);
    reset();
    _remote_thema_root_path = remote_path.isEmpty() ? _manager.appSettings()->themaRemotePath() : remote_path;
    QUrl url = QUrl::fromUserInput(_remote_thema_root_path + "/index.csv");
    if(url.isValid()) {
        LOG_INFO(QString("Thema updater :: Starting update from %1").arg(url.toString()));
        _file_downloader.startDownload(url);
    } else {
        LOG_INFO(QString("Thema updater :: Cannot start update from %1. Invalid url").arg(url.toString()));
        _progress = 1.0;
        emit updateProgress(tr("Invalid url"), _progress);
        setUpdateState(UPDATE_ERROR);
        setUpdateState(UPDATE_FINISHED);
    }
}

//******************************************************************************
/*! \brief Returns true if thema update process is completed.
 *
 *  \author Vikas Pachdha
 *
 *  \return bool : True if update is finished. False otherwise.
 ******************************************************************************/
bool ThemaUpdater_C::isProcessComplete()
{
    return _state == UPDATE_FINISHED ? true : false;
}

//******************************************************************************
/*! \brief Called when index file download finishes.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void ThemaUpdater_C::onIndexFileDownloadFinished()
{
    if(_state == UPDATE_STARTED) {
        _progress = 0.05;
        emit updateProgress(tr("Parsing server data."), _progress);
        QByteArray file_data = _file_downloader.fileData();
        QHash<QString, RemoteFileInfo> parsed_data;
        if(ParseIndexFile(file_data, parsed_data)) {
            if(parsed_data.keys().count()> 0) {
                _remote_file_data = parsed_data;
                buildLocalData();
            }
        } else {
            _progress = 1.0;
            emit updateProgress(tr("Parsing error. Aborting update."), _progress);
            setUpdateState(UPDATE_ERROR);
            setUpdateState(UPDATE_FINISHED);
        }
    }
}

//******************************************************************************
/*! \brief Called when file download is aborted.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void ThemaUpdater_C::onFileDownloadAborted()
{
    LOG_WARN("Thema updater :: File download aborted.");
    _progress = 1.0;
    emit updateProgress(tr("Network issue. Aborting update."), _progress);
    setUpdateState(UPDATE_ABORTED);
    setUpdateState(UPDATE_FINISHED);
}

//******************************************************************************
/*! \brief Parses the index file downloaded from the remote server.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] file_data : File data downloaded from remote server.
 *  \param[out] parsed_data : Parsed data.
 *
 *  \return bool : True if parsing succeeds, false otherwise.
 ******************************************************************************/
bool ThemaUpdater_C::ParseIndexFile(QByteArray file_data, QHash<QString, RemoteFileInfo> &parsed_data)
{
    bool success = false;
    QString data = QString::fromLatin1(file_data);
    if(!data.isEmpty()) {
        // Split text into lines
        QStringList lines = data.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
        if( lines.takeFirst().compare(QString(ARTIKEL::INDEX_FILE_TOKEN)) == 0 ) {

            // Parse each line
            foreach(QString line, lines) {
                success = true;
                QStringList file_params = line.split(";");
                // Parse file name and update time.
                if(file_params.count() > 1) {
                    QString file_id = file_params.at(0).toLower();
                    QString update_time_str = file_params.at(1);
                    bool ok = false;
                    qint64 msecs = update_time_str.toLongLong(&ok);
                    QDateTime update_date = QDateTime::fromMSecsSinceEpoch(msecs);
                    if(update_date.isValid() && !file_id.isEmpty()) {
                        // Params are parsed, add to structure
                        RemoteFileInfo remote_file_info;
                        remote_file_info._file_name = file_params.at(0);
                        remote_file_info._update_date = update_date;
                        parsed_data[file_id] = remote_file_info;
                        LOG_INFO(QString("Thema updater :: Parsed index file entry %1:%2")
                                 .arg(remote_file_info._file_name)
                                 .arg(update_date.toString()));
                    }
                }
            }

        } else {
            LOG_ERROR("Thema updater :: Invalid Index file.");
            success = false;
        }

    }
    return success;
}

//******************************************************************************
/*! \brief Ececutes the operations.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
bool ThemaUpdater_C::executeOperations()
{
    bool success = true;
    double factor = 0.7 / _file_operations.count();
    if(_file_operations.count() >0) {
        LOG_INFO("Thema updater :: Executing operations.");
        foreach (ThemaFileOperation_I* operation, _file_operations) {
            operation->execute();
            _progress += factor;
            updateProgress(tr("Downloading thema files."),_progress);
        }
        _progress = 1.0;
        updateProgress(tr("Update finished."),_progress);
        setUpdateState(UPDATE_FINISHED);
    } else {
        LOG_WARN("Thema updater :: No operations to execute.");
        _progress = 1.0;
        updateProgress(tr("No update is available."),_progress);
        setUpdateState(UPDATE_NOT_AVAILABLE);
        setUpdateState(UPDATE_FINISHED);
    }
    return success;
}

//******************************************************************************
/*! \brief Initiates local thema file's data.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void ThemaUpdater_C::buildLocalData()
{
    _progress = 0.1;
    emit updateProgress(tr("Comparing current thema's."), _progress);
    // thema_loader shall be deleted automatically.
    LOG_INFO("Thema updater :: building local data");
    ThemaLoader_C* thema_loader = new ThemaLoader_C(this);
    thema_loader->setRootThemaDir(_manager.appSettings()->defaultThemaDirPath());
    connect(thema_loader, SIGNAL(themaLoaded(Thema_C*)), this, SLOT(onNewthemaLoaded(Thema_C*)) );
    connect(thema_loader,SIGNAL(finishedLoading()),this, SLOT(onBuildLocalDataFinished()) );
    connect(thema_loader,SIGNAL(updateProgress(double)),this, SLOT(onThemaLoadProgress(double)));
    thema_loader->startLoading();
}

//******************************************************************************
/*! \brief Resets the operations and local data.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void ThemaUpdater_C::reset()
{
    LOG_INFO("Thema updater :: Resetting");
    _remote_file_data.clear();
    _file_operations.clear();
    _remote_thema_root_path = "";
}

//******************************************************************************
/*! \brief Called when a new thema is loaded from the local file system.
 *
 *  \details Operations are created with the help of time stamp.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] thema : Thema instance.
 ******************************************************************************/
void ThemaUpdater_C::onNewthemaLoaded(Thema_C *thema)
{
    Q_ASSERT(thema);

    QFileInfo thema_local_file_info(thema->filePath());
    if(_remote_file_data.contains(thema_local_file_info.fileName().toLower())) {
        if(_remote_file_data[thema_local_file_info.fileName().toLower()]._update_date > thema->lastUpdated()) {
            // Replace operation
            QString local_file_path = thema->filePath();
            QUrl remote_file_url = QUrl::fromUserInput(_remote_thema_root_path + "/" + thema_local_file_info.fileName());
            ThemaFileOperation_I* operation = new ThemaReplaceOperation_C(local_file_path,
                                                                          remote_file_url,
                                                                          thema->experiencePoints());
            _file_operations.append(operation);
            LOG_INFO(QString("Thema updater :: Added replace operation %1:%2").arg(local_file_path).arg(remote_file_url.toString()));
        }
        _remote_file_data.remove(thema_local_file_info.fileName().toLower());
    } else {
        // Remove operation
        ThemaFileOperation_I* operation = new ThemaDeleteOperation_C(thema->filePath());
        _file_operations.append(operation);
        LOG_INFO(QString("Thema updater :: Added remove operation %1").arg(thema->filePath()));
    }

    // Require data is process. Thema instance is no longer required.
    delete thema;
}

//******************************************************************************
/*! \brief Called when local data build is completed. Operations execution is initiated.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void ThemaUpdater_C::onBuildLocalDataFinished()
{
    foreach (QString key, _remote_file_data.keys()) {
        // Add operation
        QString local_file_path = _manager.appSettings()->defaultThemaDirPath() + QDir::separator()+ _remote_file_data[key]._file_name;
        QUrl remote_file_url = QUrl::fromUserInput(_remote_thema_root_path + "/" + _remote_file_data[key]._file_name);
                ThemaFileOperation_I* operation = new ThemaAddOperation_C(local_file_path, remote_file_url.toString());
        _file_operations.append(operation);
        LOG_INFO(QString("Thema updater :: Added add operation %1").arg(remote_file_url.toString()));
    }

    _progress = 0.30;
    emit updateProgress(tr("Comparing current thema's."), _progress);
    executeOperations();
}

//******************************************************************************
/*! \brief  Called to notify the thema loading progress.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void ThemaUpdater_C::onThemaLoadProgress(double progress)
{
    emit updateProgress(tr("Comparing current thema's."), _progress + (progress*0.20));
}

//******************************************************************************
/*! \brief  Helper method to set update state.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] new_state : New state to set
 ******************************************************************************/
void ThemaUpdater_C::setUpdateState(ThemaUpdateState_TP new_state)
{
    if(_state != new_state) {
        _state = new_state;
        LOG_INFO(QString("Thema updater :: Update state changed : %1").arg(_state));
        emit updateStateChanged(_state);
        if(_state == UPDATE_FINISHED) {
            emit updateFinished();
        }
    }
}
