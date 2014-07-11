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
    _progress(0.0)
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
    emit updateResponse(UPDATE_STARTED);
    emit updateProgress(tr("Checking for app update."), _progress);
    QUrl url = QUrl::fromUserInput(_manager.appSettings()->versionInfoPath());
    if(url.isValid()) {
        LOG_INFO(QString("App updater :: Starting update from %1").arg(url.toString()));
        _file_downloader.startDownload(url);
    } else {
        LOG_INFO(QString("APP updater :: Cannot start update from %1. Invalid url").arg(url.toString()));
        _progress = 1.0;
        emit updateProgress(tr("Invalid url"), _progress);
        emit updateResponse(UPDATE_ERROR);
    }
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
        _progress = 1.0;
        emit updateProgress(tr("Comparing current thema's."), _progress);
        _download_url = QUrl::fromUserInput(download_url);
        QDesktopServices::openUrl(_download_url);
    } else {
        _progress = 1.0;
        emit updateProgress(tr("Parsing error. Aborting update."), _progress);
        emit updateResponse(UPDATE_ERROR);
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
    emit updateResponse(UPDATE_ABORTED);
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
            QDomElement latestVersionElem = root.firstChildElement("latest_version");
            QDomAttr versionAttr = latestVersionElem.attributeNode("id");
            QString versionStr = versionAttr.value();

            bool ok = false;
            int version = versionStr.toInt(&ok);
            if(ok) {
                if(version > APP_VERSION) {
                    success = true;
                    download_url = "http://www.vystosi.com/#download";
                }
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
/*! \brief  Called to notify the version file loading progress.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void AppUpdater_C::onFileLoadProgress(double progress)
{
    emit updateProgress(tr("Contacting server."), _progress + (progress*0.50));
}
