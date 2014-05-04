//******************************************************************************
/*! \file thema_replace_operation.h Declaration of \ref ThemaReplaceOperation_C
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
#ifndef THEMA_REPLACE_OPERATION_H
#define THEMA_REPLACE_OPERATION_H

// System includes
#include <QEventLoop>
#include <QObject>
#include <QUrl>

// Project includes
#include "file_downloader.h"
#include "thema_file_operation.h"


//******************************************************************************
/*! \brief Replaces a thema file operation.
 *
 *  \details Algorithm replaces a thema file.
 *
 *  \author Vikas Pachdha
 *
 *  \see \ref ThemaDeleteOperation_C, \ref ThemaAddOperation_C
 ******************************************************************************/
class ThemaReplaceOperation_C : public QObject, public ThemaFileOperation_I
{
    Q_OBJECT
public:
    ThemaReplaceOperation_C(QString local_file_path, QUrl remote_file_url,  int old_experience);

public:
    virtual bool execute();

private slots:
    void onFileDownloadFinished();
    void onFileDownloadAborted();

private:
    FileDownloader_C _file_downloader;
    QString _local_file_path;
    QUrl _remote_file_url;
    int _old_experience;
    QEventLoop _event_loop;
};

#endif // THEMA_REPLACE_OPERATION_H
