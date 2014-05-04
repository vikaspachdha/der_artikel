//******************************************************************************
/*! \file file_downloader.cpp Implementation of \ref FileDownloader_C
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
#include <QDebug>
#include <QNetworkRequest>

// Interface for this file
#include "file_downloader.h"

// Framework and lib includes
#include "log4qt/log_defines.h"


//******************************************************************************
/*! \brief Constructor.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] parent : Parent instance.
 ******************************************************************************/
FileDownloader_C::FileDownloader_C(QObject *parent) :
    QObject(parent),
    _network_reply(0)
{
}
//******************************************************************************
/*! \brief Starts a file download.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] url : Url of the file to be downloaded.
 ******************************************************************************/
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

//******************************************************************************
/*! \brief Stops the on going file download.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
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

//******************************************************************************
/*! \brief Called periodically during download progess.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] bytes_recieved : Number of bytes recieved.
 *  \param[in] total_bytes : Total number of bytes to download.
 ******************************************************************************/
void FileDownloader_C::onDownloadProgress(qint64 bytes_recieved, qint64 total_bytes)
{
    LOG_INFO(QString("File downloader :: Download progress %1 bytes %2").
             arg(bytes_recieved).
             arg((bytes_recieved)/total_bytes));
    emit downloadProgress(double(bytes_recieved)/total_bytes);
}

//******************************************************************************
/*! \brief Called when some error occurs during file download.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] errorCode : Error code.
 ******************************************************************************/
void FileDownloader_C::onError(QNetworkReply::NetworkError errorCode)
{
    LOG_ERROR(QString("File downloader :: File download error. Error code:: %1").arg(errorCode));
    emit downloadAborted();
}

//******************************************************************************
/*! \brief Called when file download finishes.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void FileDownloader_C::onFinished()
{
    LOG_INFO("File downloader :: File download finished");
    _file_data.append(_network_reply->readAll());
    _network_reply->deleteLater();
    _network_reply = 0;
    emit downloadFinished();
}

//******************************************************************************
/*! \brief Called when data is received after a request is made.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void FileDownloader_C::onDataRecieved()
{
    LOG_INFO("File downloader :: data received");
    _file_data.append(_network_reply->readAll());
}
