//******************************************************************************
/*! \file page.h Declaration of \ref Page_C
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
#ifndef PAGE_H
#define PAGE_H

// System includes
#include <QObject>

// Project includes
#include "page_i.h"

//******************************************************************************
/*! \brief Abstract class for a Page entity. Implements the IPage interface with defaults
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
class Page_C : public QObject, public Page_I
{
    Q_OBJECT

public:
    explicit Page_C(Manager_C::PageId_TP page_id, Manager_C& page_manager, QObject *parent = 0);

public:
    virtual Manager_C::PageId_TP pageId() const;
    virtual bool canEnter() const;
    virtual void enter(Manager_C::PageId_TP prev_page_id);
    virtual bool canLeave() const;
    virtual void leave(Manager_C::PageId_TP next_page_id);

protected:
    QQuickItem* titleItem();
    QQuickItem* pageItem();
    QQuickItem* panelItem();

protected:
    //! Page id
    Manager_C::PageId_TP _page_id;
    //! Page manager instance
    Manager_C& _page_manager;
};

#endif // PAGE_H
