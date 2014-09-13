//******************************************************************************
/*! \file result_page.cpp Implementation of \ref ResultPage_C
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

// System includes
#include <QQmlContext>

// Interface for this file
#include "result_page.h"

// Framework and lib includes
#include "log4qt/log_defines.h"

//******************************************************************************
/*! \brief Constructor
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] page_manager : \ref Manager_C instance.
 *  \param[in] root_context : QML root context instance.
 *  \param[in] parent : Parent instance.
 ******************************************************************************/
ResultPage_C::ResultPage_C(Manager_C &page_manager, QQmlContext &root_context, QObject *parent)
    :Page_C(Manager_C::RESULT_PAGE, page_manager, parent),
    _view_type(VIEW_CORRECTION)
{
    root_context.setContextProperty("result_page_instance",this);
}

//******************************************************************************
/*! \brief Called when page enters. Default view type "VIEW_CORRECTION" is set.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] prev_page_id : Previous page id.
 ******************************************************************************/
void ResultPage_C::enter(Manager_C::PageId_TP prev_page_id)
{
    Q_UNUSED(prev_page_id)
    setViewType(VIEW_CORRECTION);
}

//******************************************************************************
/*! \brief Sets the \ref ViewType_TP "view type".
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] view_type : The \ref ViewType_TP "view type" to change to.
 ******************************************************************************/
void ResultPage_C::setViewType(const ResultPage_C::ViewType_TP &view_type)
{
    if(_view_type != view_type) {
        _view_type = view_type;
        emit viewTypeChanged();
    }
}
