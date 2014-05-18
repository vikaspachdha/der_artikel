//******************************************************************************
/*! \file file_downloader.h Declaration of \ref FileDownloader_C
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
#ifndef FILE_DOWNLOADER_H
#define FILE_DOWNLOADER_H

// System includes
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QTextStream>


//******************************************************************************
/*! \brief Utility class to download a file and return download data.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
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
    //! Emitted periodicaly after download start to signal download progress.
    void downloadProgress(double progress);
    //! Emitted to signal download finish.
    void downloadFinished();
    //! Emiited if download is canceled or aborted.
    void downloadAborted();

private:
    QNetworkAccessManager _network_manager;
    QNetworkReply* _network_reply;
    //! Downloaded file data.
    QByteArray _file_data;
    QTextStream* _data_steam;
};

#endif // FILE_DOWNLOADER_H
