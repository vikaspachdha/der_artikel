//******************************************************************************
/*! \file article.cpp Implementation of \ref Article_C
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

#include "article.h"
#include "log4qt/log_defines.h"


//******************************************************************************
/*! \brief Constructor
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] parent : Parent object instance.
 ******************************************************************************/
Article_C::Article_C(QObject *parent) :
    QObject(parent)
{
}

//*****************************************************************************
/*! \brief Returns corresponding text for the artikel value.
*
*   \author Vikas Pachdha
*
*   \param[in] artikel : Artikel value.
*
*   \return QString : Artikel text.
******************************************************************************/
QString Article_C::ArtikelText(Article_C::Artikel artikel)
{
    QString text;
    switch(artikel)
    {
    case DER:
        text = "Der";
        break;

    case DIE:
        text = "Die";
        break;

    case DAS:
        text = "Das";
        break;

    default:
        text = "";
        LOG_DEBUG("ArtikelText::INVALID");
        break;

    }

    return text;
}
