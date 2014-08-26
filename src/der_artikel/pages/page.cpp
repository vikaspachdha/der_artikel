//******************************************************************************
/*! \file page.cpp Implementation of \ref Page_C
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
#include "page.h"

// Framework and lib includes
#include "log4qt/log_defines.h"

// Project includes
#include "manager.h"


/********************************************************************************/
/*! \brief Constructor.
 *
 *  \author Vikas Pachdha.
 *
 *  \param[in]  page_id Page id of the page.
 *  \param[in]  page_manager : \ref Manager_C instance.
 *  \param[in]  parent Parent instance for this instance of CImageArchivePage.
 *********************************************************************************/
Page_C::Page_C(Manager_C::PageId_TP page_id, Manager_C &page_manager, QObject *parent) :
    QObject(parent),
    _page_id(page_id),
    _page_manager(page_manager)
{
    LOG_DEBUG(QString("Page_C(PageId_TP %1)").arg(page_id));
}

/********************************************************************************/
/** \brief Returns the page id of the page.
 *
 *  \author Vikas Pachdha.
 *
 *  \return Manager_C::PageId_TP Page id of the page
 *********************************************************************************/
Manager_C::PageId_TP Page_C::pageId() const
{
    return _page_id;
}


/********************************************************************************/
/*! \brief \ref Manager_C calls this method to decide whether preconditions are
 *  met to enter this page. Override this method to define the preconditions for
 *  the corresponding page.
 *
 *  \author Vikas Pachdha.
 *
 *  \return bool True i.e page can be switched.
 *********************************************************************************/
bool Page_C::canEnter() const
{
    return true;
}

/********************************************************************************/
/*! \brief \ref Manager_C calls this method to just before entering the page.
 *  Override this method to write initialization code for the corresponding page.
 *
 *  \author Vikas Pachdha.
 *
 *********************************************************************************/
void Page_C::enter(Manager_C::PageId_TP prev_page_id)
{
    Q_UNUSED(prev_page_id)
}

/********************************************************************************/
/*! \brief \ref Manager_C calls this method to decide whether conditions are
 *  met to leave this page. Override this method to define the conditions for
 *  the corresponding page.
 *
 *  \author Vikas Pachdha.
 *
 *  \return bool True i.e page can be switched off.
 *********************************************************************************/
bool Page_C::canLeave() const
{
    return true;
}

/********************************************************************************/
/** \brief \ref Manager_C calls this method to just after leaving the page.
 *  Override this method to write clean up code for the corresponding page.
 *
 *  \author Vikas Pachdha.
 *
 *  \param next_page_id Next page's id i.e. page to be switched to.
 *
 *********************************************************************************/
void Page_C::leave(Manager_C::PageId_TP next_page_id)
{
    Q_UNUSED(next_page_id)
}

/********************************************************************************/
/** \brief Returns the title QML Item of the page.
 *
 *  \author Vikas Pachdha.
 *
 *  \return QQuickItem* : Title QML Item of the page.
 *********************************************************************************/
QQuickItem *Page_C::titleItem()
{
    return _page_manager.titleItem(_page_id);
}

/********************************************************************************/
/** \brief Returns the main QML Item of the page.
 *
 *  \author Vikas Pachdha.
 *
 *  \return QQuickItem* : Main QML Item of the page.
 *********************************************************************************/
QQuickItem *Page_C::pageItem()
{
    return _page_manager.pageItem(_page_id);
}

/********************************************************************************/
/** \brief Returns the panel QML Item of the page.
 *
 *  \author Vikas Pachdha.
 *
 *  \return QQuickItem* : Panel QML Item of the page.
 *********************************************************************************/
QQuickItem *Page_C::panelItem()
{
    return _page_manager.panelItem(_page_id);
}
