//******************************************************************************
/*! \file thema_page.h Declaration of \ref ThemaPage_C.
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
#ifndef THEMA_PAGE_H
#define THEMA_PAGE_H

// Project includes
#include "page.h"


//******************************************************************************
/*! \brief Entity class for thema page. The entity defines menu items for the
 *  thema page and how to use the shared user interface elements such as menu and
 *  status bar.
 *
 *  \details User is provided with user interface to select a thema to play.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
class ThemaPage_C : public Page_C
{
    Q_OBJECT
public:
    explicit ThemaPage_C(Manager_C& page_manager, QObject *parent = 0);

public:
    virtual void enter(Manager_C::PageId_TP prev_page_id);
};

#endif // THEMA_PAGE_H
