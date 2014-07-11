//******************************************************************************
/*! \file app_updater.h Declaration of \ref AppUpdater_C
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
#ifndef APP_UPDATER_H
#define APP_UPDATER_H
// System includes
#include <QHash>
#include <QObject>
#include <QUrl>
#include <QVector>

// Project includes
#include "file_downloader.h"

// Forward declaration
class Manager_C;
class ThemaFileOperation_I;
class Thema_C;

//******************************************************************************
/*! \brief Application updater class.
 *
 *  \details Updates the app from the remote server.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
class AppUpdater_C : public QObject
{
    Q_OBJECT
    Q_ENUMS(UpdateResponse_TP)

public:

    //! Update response codes
    enum UpdateResponse_TP {
        UPDATE_STARTED = 1, //! Update process started.
        UPDATE_AVAILABLE, //! Update is available.
        UPDATE_NOT_AVAILABLE, //! Update is not available.
        UPDATE_ERROR, //! Error encountered while updating.
        UPDATE_FINISHED, //! Update finished.
        UPDATE_ABORTED //! Update process is aborted.
    };

public:
    explicit AppUpdater_C(Manager_C& manager, QObject *parent = 0);

public:
    Q_INVOKABLE void checkUpdate();

private slots:
    void onVersionFileDownloadFinished();
    void onFileDownloadAborted();
    void onFileLoadProgress(double progress);

signals:
    //! Emitted when a update response is received.
    void updateResponse(UpdateResponse_TP response_code);

    //! Emitted to notify progress. String provides the information of update stage
    //! and value is progess that ranges between 0 to 1 where 1 is 100 %.
    void updateProgress(QString info, double progress);

private:
    bool parseVersionFile(QByteArray file_data, QString &download_url);

private:
    //! Manager instance reference.
    Manager_C& _manager;
    //! File downloader instance.
    FileDownloader_C _file_downloader;
    //! Update progress.
    double _progress;
    QUrl _download_url;
};

#endif // APP_UPDATER_H
