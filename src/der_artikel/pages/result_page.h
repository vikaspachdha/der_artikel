//******************************************************************************
/*! \file result_page.h Declaration of \ref ResultPage_C
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
#ifndef RESULT_PAGE_H
#define RESULT_PAGE_H

// Project includes
#include "page.h"

// Forward declaration
class QQmlContext;


//******************************************************************************
/*! \brief Entity class for result page. The entity defines menu items for the
 *  help page and how to use the shared user interface elements such as menu and
 *  status bar.
 *
 *  \details User is provided with mistakes and corrections.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
class ResultPage_C : public Page_C
{
    Q_OBJECT
    Q_PROPERTY(ViewType_TP view_type READ viewType WRITE setViewType NOTIFY viewTypeChanged)
    Q_ENUMS(ViewType_TP)

public:
    //! View type.
    enum ViewType_TP {
        VIEW_CORRECTION=1,
        VIEW_MISTAKES,
    };

public:
    ResultPage_C(Manager_C& page_manager,QQmlContext &root_context, QObject *parent);

public:
    virtual void enter(Manager_C::PageId_TP prev_page_id);

public:
    //! Returns the current view type to show.
    ViewType_TP viewType() const { return _view_type; }
    void setViewType(const ViewType_TP &view_type);

signals:
    //! Emitted when sub page changes.
    void viewTypeChanged();

private:
    //! Sub page.
    ViewType_TP _view_type;
};

#endif // RESULT_PAGE_H
