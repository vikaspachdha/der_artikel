//******************************************************************************
/*! \file thema_loader.h Declaration of \ref ThemaLoader_C
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
#ifndef THEMA_LOADER_H
#define THEMA_LOADER_H

// System includes
#include <QObject>
#include <QString>
#include <QRunnable>


// Forward declarations
class Thema_C;


//******************************************************************************
/*! \brief Utility class to load thema files.
 *
 *  \details Provides methods to load thema file asynchronously and synchronously.
 *  calling \ref ThemaLoader_C::startLoading "startLoading" starts loading thema
 *  asynchronously from the default thema directory. Connect to signal \ref
 *  ThemaLoader_C::themaLoaded "themaLoaded" to receive loaded thema file.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
class ThemaLoader_C: public QObject, public QRunnable
{
    Q_OBJECT
public:
    ThemaLoader_C(QObject* thema_parent=0, QObject* parent = 0);

protected:
    virtual void run();

public:
    Thema_C* loadThema(QString file_path, bool defered = true);
    void startLoading();

signals:
    //! Emitted when a thema is loaded. Thema object ownership is with the receiver class.
    void themaLoaded(Thema_C* new_thema);

    //! Emitted when asynchronously thema loading finishes.
    void finishedLoading();

    //! emitted to notify progess on asynchronous load.
    void updateProgress(double);

private:

    //! Stores absolute path to default thema directory.
    QString _root_dir;

    //! QObject instance used as thema parent.
    QObject* _thema_parent;
};

#endif // THEMA_LOADER_H
