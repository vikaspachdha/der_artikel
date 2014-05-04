//******************************************************************************
/*! \file help_page.h Declaration of \ref HelpPage_C
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
#ifndef HELP_PAGE_H
#define HELP_PAGE_H

// Project includes
#include "page.h"

// Forward declaration
class QQmlContext;


//******************************************************************************
/*! \brief Entity class for help page. The entity defines menu items for the
 *  help page and how to use the shared user interface elements such as menu and
 *  status bar.
 *
 *  \details User is provided with usage help user interface.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
class HelpPage_C : public Page_C
{
    Q_OBJECT
    Q_PROPERTY(QString sub_page READ subPage NOTIFY subPageChanged)
    Q_PROPERTY(SubPage_TP sub_page_type READ subPageType WRITE setSubPageType NOTIFY subPageChanged)
    Q_PROPERTY(QString title READ title NOTIFY subPageChanged)

    Q_ENUMS(SubPage_TP)

public:
    //! Sub pages within help page.
    enum SubPage_TP {
        GENERAL=1,
        RULES,
        SCORING,
        OTHERS
    };

public:
    explicit HelpPage_C(Manager_C& page_manager, QQmlContext& root_context, QObject *parent = 0);

public:
    virtual void enter(Manager_C::PageId_TP prev_page_id);

public:

    QString title() const;

    QString subPage() const;

    //! Returns the current selected sub page.
    SubPage_TP subPageType() const { return _sub_page_type; }
    void setSubPageType(const SubPage_TP &sub_page_type);

signals:
    //! Emitted when sub page changes.
    void subPageChanged();

private:
    //! Root QML context instance.
    QQmlContext& _root_context;
    //! Sub page.
    SubPage_TP _sub_page_type;
};

#endif // HELP_PAGE_H
