//******************************************************************************
/*! \file thema_replace_operation.cpp Implementation of \ref ThemaReplaceOperation_C
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
#include <QFile>

// Interface for this file
#include "thema_replace_operation.h"

// Framework and lib includes
#include "data/thema_loader.h"
#include "data/thema.h"


//******************************************************************************
/*! \brief Constructor.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] local_file_path : Path to local file.
 *  \param[in] remote_file_url : Remote file url to be downloaded.
 *  \param[in] old_experience : Old experience points.
 ******************************************************************************/
ThemaReplaceOperation_C::ThemaReplaceOperation_C(QString local_file_path, QUrl remote_file_url, int old_experience):
    QObject(0),
    _local_file_path(local_file_path),
    _remote_file_url(remote_file_url),
    _old_experience(old_experience)
{
    connect(&_file_downloader, SIGNAL(downloadFinished()), this, SLOT(onFileDownloadFinished()));
    connect(&_file_downloader, SIGNAL(downloadAborted()), this, SLOT(onFileDownloadAborted()));
}

//******************************************************************************
/*! \brief Executes the operation and returns when finished.
 *
 *  \details The UI is responsive when operation is being performed.
 *
 *  \author Vikas Pachdha
 *
 *  \return bool : True if operation succeeds, false othewise.
 ******************************************************************************/
bool ThemaReplaceOperation_C::execute()
{
    bool success = true;
    if(_remote_file_url.isValid()) {
        _file_downloader.startDownload(_remote_file_url);
        success = _event_loop.exec() == 0 ?true:false ;
    } else {
        success = false;
    }
    return success;
}

//******************************************************************************
/*! \brief Called when file download finishes.
 *
 *  \details  The file is replaced and execute method returns with success.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void ThemaReplaceOperation_C::onFileDownloadFinished()
{
    QByteArray file_data = _file_downloader.fileData();
    int exit_code = -1;
    QFile file(_local_file_path);
    if (file.open(QFile::WriteOnly)) {
        file.write(file_data.data(),file_data.size());
        file.flush();
        file.close();
        ThemaLoader_C thema_loader;
        Thema_C* thema = thema_loader.loadThema(_local_file_path,false);
        if(thema) {
            // reset the old experience points
            thema->addExperiencePoints(_old_experience);
            thema->save();
            delete thema;
            exit_code = 0;
        } else {
            // Something went bad. Thema not replaced
            QFile::remove(_local_file_path);
        }
    }
    _event_loop.exit(exit_code);
}

//******************************************************************************
/*! \brief Called when file download is aborted.
 *
 *  \details Execute method returns with failure.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void ThemaReplaceOperation_C::onFileDownloadAborted()
{
    _event_loop.exit(-1);
}


