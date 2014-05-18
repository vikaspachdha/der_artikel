//******************************************************************************
/*! \file image_provider.h Declaration of \ref ImageProvider_C
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
#ifndef IMAGE_PROVIDER_H
#define IMAGE_PROVIDER_H

// System includes
#include <QHash>
#include <QQuickImageProvider>


//******************************************************************************
/*! \brief Main image provider for the QML.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
class ImageProvider_C : public QQuickImageProvider
{
public:
    explicit ImageProvider_C();

public:
    void addImage(QString id, QPixmap pixmap);

public:
    virtual QPixmap	requestPixmap(const QString & id, QSize * size, const QSize & requestedSize);

private:
    //! Stores images with their id's
    QHash<QString, QPixmap> _images;
};

#endif // IMAGE_PROVIDER_H
