//******************************************************************************
/*! \file common.cpp Implementation of utility api's.
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
#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>
#include "common.h"


namespace ARTIKEL{

//******************************************************************************
/*! \brief Returns the complete path of resource by appending the path of the
 * resource's directory of a resource requested.
 *
 *  \details Path changes as per the platform.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] path : Releative path of the resource.
 *
 *  \return QString : Complete path of the resource.
 ******************************************************************************/
QString GetResourcePath(const QString &path)
{    
#if defined(Q_OS_IOS)
    if (!QDir::isAbsolutePath(path))
        return QString::fromLatin1("%1/%2")
                .arg(QCoreApplication::applicationDirPath(), path);
#elif defined(Q_OS_MAC)
    if (!QDir::isAbsolutePath(path))
        return QString::fromLatin1("%1/../Resources/%2")
                .arg(QCoreApplication::applicationDirPath(), path);
#elif defined(Q_OS_BLACKBERRY)
    if (!QDir::isAbsolutePath(path))
        return QString::fromLatin1("app/native/%1").arg(path);
#elif !defined(Q_OS_ANDROID)
    QString pathInInstallDir =
            QString::fromLatin1("%1/../%2").arg(QCoreApplication::applicationDirPath(), path);
    if (QFileInfo(pathInInstallDir).exists())
        return pathInInstallDir;
    pathInInstallDir =
            QString::fromLatin1("%1/%2").arg(QCoreApplication::applicationDirPath(), path);
    if (QFileInfo(pathInInstallDir).exists())
        return pathInInstallDir;
#elif defined(Q_OS_ANDROID_NO_SDK)
    return QLatin1String("/data/user/qt/") + path;
#endif
    return path;
}

}
