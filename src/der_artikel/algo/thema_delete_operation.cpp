//******************************************************************************
/*! \file thema_delete_operation.cpp Implementation of \ref ThemaDeleteOperation_C
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
#include "thema_delete_operation.h"

//******************************************************************************
/*! \brief Constructor.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] local_file_path : Path to local file to be deleted.
 ******************************************************************************/
ThemaDeleteOperation_C::ThemaDeleteOperation_C(QString local_file_path):
    QObject(0),
    _local_file_path(local_file_path)
{
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
bool ThemaDeleteOperation_C::execute()
{
    return QFile::remove(_local_file_path);
}
