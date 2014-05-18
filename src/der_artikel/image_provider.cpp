//******************************************************************************
/*! \file image_provider.cpp Implementation of \ref ImageProvider_C
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

// Interface for this file
#include "image_provider.h"

// Framework and lib includes
#include "log4qt/log_defines.h"


//******************************************************************************
/*! \brief Constructor
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
ImageProvider_C::ImageProvider_C() :
    QQuickImageProvider(QQuickImageProvider::Pixmap)
{
}

//******************************************************************************
/*! \brief Add image to the store against the id.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] id : Id of the image.
 ******************************************************************************/
void ImageProvider_C::addImage(QString id, QPixmap pixmap)
{
    LOG_INFO("Image provider :: Image added for id - "+id);
    _images[id] = pixmap;
}

//******************************************************************************
/*! \brief Returns image against the requested id. For unavailable images, null
 *  pixmaps shall be returned.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] id : Id of the image requested.
 *  \param[in] size : Original size of the image.
 *  \param[in] requestedSize : corresponds to the Image::sourceSize requested by
 *  an Image item.
 *
 *  \return QPixmap : Requested image.
 ******************************************************************************/
QPixmap ImageProvider_C::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(size);
    Q_UNUSED(requestedSize);
    LOG_INFO("Image provider :: Image request for id - "+id);
    return _images[id];
}
