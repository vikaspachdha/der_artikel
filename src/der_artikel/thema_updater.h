//******************************************************************************
/*! \file thema_updater.h Declaration of \ref ThemaUpdater_C
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
#ifndef THEMA_UPDATER_H
#define THEMA_UPDATER_H
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
/*! \brief Thema updater class.
 *
 *  \details Updates the thema from the remote server.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
class ThemaUpdater_C : public QObject
{
    Q_OBJECT
    Q_ENUMS(UpdateResponse_TP)
public:

    //! Update response codes
    enum UpdateResponse_TP {
        UPDATE_AVAILABLE=1, //! Update is available.
        UPDATE_NOT_AVAILABLE, //! Update is not available.
        UPDATE_ERROR, //! Error encountered while updating.
        UPDATE_FINISHED //! Update finished.
    };

public:
    explicit ThemaUpdater_C(Manager_C& manager, QObject *parent = 0);

public:
    Q_INVOKABLE void checkUpdate();

private slots:
    void onFileDownloadFinished();
    void onFileDownloadAborted();
    void onNewthemaLoaded(Thema_C *new_thema);
    void onBuildLocalDataFinished();

signals:
    //! Emitted when a update response is received.
    void updateResponse(UpdateResponse_TP response_code);

private:
    bool ParseIndexFile(QByteArray file_data, QHash<QString, QDateTime>& parsed_data);
    bool executeOperations();
    void buildLocalData();
    void reset();

private:
    //! Manager instance reference.
    Manager_C& _manager;
    //! File downloader instance.
    FileDownloader_C _file_downloader;
    //! Remote file data.
    QHash<QString, QDateTime> _remote_file_data;
    //! File operations.
    QVector<ThemaFileOperation_I*> _file_operations;
};

#endif // THEMA_UPDATER_H
