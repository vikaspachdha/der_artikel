//******************************************************************************
/*! \file app_updater.cpp Implementation of \ref AppUpdater_C
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
#include <QDesktopServices>
#include <QDomDocument>

// Interface for this file
#include "app_updater.h"

// Framework and lib includes
#include "data/version.h"
#include "log4qt/log_defines.h"

// Project includes
#include "manager.h"
#include "settings.h"

//******************************************************************************
/*! \brief Constructor
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] manager : \ref Manager_C class reference.
 *  \param[out] parent : Parent instance
 ******************************************************************************/
AppUpdater_C::AppUpdater_C(Manager_C &manager, QObject *parent) :
    QObject(parent),
    _manager(manager),
    _progress(0.0),
    _state(INVALID)
{
    connect(&_file_downloader, SIGNAL(downloadFinished()), this, SLOT(onVersionFileDownloadFinished()));
    connect(&_file_downloader, SIGNAL(downloadAborted()), this, SLOT(onFileDownloadAborted()));
}

//******************************************************************************
/*! \brief Initiates checking if app update is available or not.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void AppUpdater_C::checkUpdate()
{
    _progress = 0.0;
    _download_url = QUrl();
    setUpdateState(UPDATE_STARTED);
    emit updateProgress(tr("Checking for app update."), _progress);
    QUrl url = QUrl::fromUserInput(_manager.appSettings()->versionInfoPath());
    if(url.isValid()) {
        LOG_INFO(QString("App updater :: Starting update from %1").arg(url.toString()));
        _file_downloader.startDownload(url);
    } else {
        LOG_INFO(QString("APP updater :: Cannot start update from %1. Invalid url").arg(url.toString()));
        _progress = 1.0;
        emit updateProgress(tr("Invalid url"), _progress);
        setUpdateState(UPDATE_ERROR);
        setUpdateState(UPDATE_FINISHED);
    }
}

//******************************************************************************
/*! \brief Initiates update download if app update is available.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void AppUpdater_C::startUpdate()
{
   if(_download_url.isValid()) {
       QDesktopServices::openUrl(_download_url);
   }
}

//******************************************************************************
/*! \brief Aborts app update.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void AppUpdater_C::abortUpdate()
{
    if(_file_downloader.isDownloading()) {
        _file_downloader.stopDownload();
    }
    setUpdateState(UPDATE_ABORTED);
    setUpdateState(UPDATE_FINISHED);
}

//******************************************************************************
/*! \brief Returns true if app update process is completed.
 *
 *  \author Vikas Pachdha
 *
 *  \return bool : True if update is finished. False otherwise.
 ******************************************************************************/
bool AppUpdater_C::isProcessComplete()
{
    return _state == UPDATE_FINISHED ? true : false;
}

//******************************************************************************
/*! \brief Called when version file download finishes.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void AppUpdater_C::onVersionFileDownloadFinished()
{
    _progress = 0.50;
    emit updateProgress(tr("Checking for new releases."), _progress);
    QByteArray file_data = _file_downloader.fileData();
    QString download_url;
    if(parseVersionFile(file_data, download_url)) {
        LOG_INFO(QString("App updater :: app update found. Url : %1").arg(download_url));
        _progress = 1.0;
        emit updateProgress(tr("Update available."), _progress);
        _download_url = QUrl::fromUserInput(download_url);
        setUpdateState(UPDATE_AVAILABLE);
    } else {
        _progress = 1.0;
        emit updateProgress(tr("No App update available."), _progress);
        setUpdateState(UPDATE_NOT_AVAILABLE);
        setUpdateState(UPDATE_FINISHED);
    }
}

//******************************************************************************
/*! \brief Called when version file download is aborted.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void AppUpdater_C::onFileDownloadAborted()
{
    LOG_WARN("App updater :: File download aborted.");
    _progress = 1.0;
    emit updateProgress(tr("Network issue. Aborting update."), _progress);
    setUpdateState(UPDATE_ABORTED);
    setUpdateState(UPDATE_FINISHED);
}

//******************************************************************************
/*! \brief Parses the version file downloaded from the remote server.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] file_data : File data downloaded from remote server.
 *  \param[out] download_url : App update url in case update is available.
 *
 *  \return bool : True if update is available, false otherwise.
 ******************************************************************************/
bool AppUpdater_C::parseVersionFile(QByteArray file_data, QString& download_url)
{
    bool success = false;
    QString data = QString::fromLatin1(file_data);
    if(!data.isEmpty()) {
        QDomDocument version_info_doc;
        QString error_msg;
        int error_line;
        int error_col;
        if(version_info_doc.setContent(data, &error_msg, &error_line, &error_col)) {
            QDomElement root = version_info_doc.firstChildElement("version_info");
            QDomElement platformElem = root.firstChildElement("platform");
            while(!platformElem.isNull()) {
                QString platformId = platformElem.attributeNode("id").value();
                LOG_DEBUG("App updater :: checking app update for platform : " + platformId);
                if(platformId.compare(_manager.appSettings()->platformId(),Qt::CaseInsensitive) == 0)
                {
                    QString versionStr = platformElem.attributeNode("latest_version").value();
                    bool ok = false;
                    int version = versionStr.toInt(&ok);
                    if(ok) {
                        if(version > APP_VERSION) {
                            QDomElement download_url_element = platformElem.firstChildElement("url");
                            download_url = download_url_element.text();
                            LOG_DEBUG("App updater :: Latest version available, url: " + download_url);
                            success = true;
                        }
                    }
                    break;
                }
                platformElem = platformElem.nextSiblingElement();
            }
        } else {
            LOG_ERROR(QString("Invalid version file. %1 Line:%2,  Col:%3").
                      arg(error_msg).
                      arg(error_line).
                      arg(error_col));
        }

    }
    return success;
}

//******************************************************************************
/*! \brief  Helper method to set update state.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] new_state : New state to set
 ******************************************************************************/
void AppUpdater_C::setUpdateState(AppUpdater_C::UpdateState_TP new_state)
{
    if(_state != new_state) {
        _state = new_state;
        LOG_INFO(QString("App updater :: Update state changed : %1").arg(_state));
        emit updateStateChanged(_state);
        if(_state == UPDATE_FINISHED) {
            emit updateFinished();
        }
    }
}

//******************************************************************************
/*! \brief  Called to notify the version file loading progress.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void AppUpdater_C::onFileLoadProgress(double progress)
{
    emit updateProgress(tr("Contacting server."), _progress + (progress*0.50));
}
