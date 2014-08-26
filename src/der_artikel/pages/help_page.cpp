//******************************************************************************
/*! \file help_page.cpp Implementation of \ref HelpPage_C
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
#include "help_page.h"

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
HelpPage_C::HelpPage_C(Manager_C& page_manager,QQmlContext &root_context, QObject *parent) :
    Page_C(Manager_C::HELP_PAGE, page_manager, parent),
    _root_context(root_context),
    _sub_page_type(GENERAL)
{
    _root_context.setContextProperty("help_page_instance",this);
}

//******************************************************************************
/*! \brief Called when page enters. Default sub page "General" is set.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] prev_page_id : Previous page id.
 ******************************************************************************/
void HelpPage_C::enter(Manager_C::PageId_TP prev_page_id)
{
    Q_UNUSED(prev_page_id)
    setSubPageType(GENERAL);
}

//******************************************************************************
/*! \brief Returns title to be set on page as per the current sub page selected.
 *
 *  \author Vikas Pachdha
 *
 *  \return QString : Title to be set on page.
 ******************************************************************************/
QString HelpPage_C::title() const
{
    QString title = "";
    switch(_sub_page_type) {
    case GENERAL:
        title = tr("General");
        break;
    case RULES:
        title = tr("Rules");
        break;
    case SCORING:
        title = tr("Scoring");
        break;
    case OTHERS:
        title = tr("Contact");
        break;
    default:
        break;
    }

    return title;
}

//******************************************************************************
/*! \brief Returns sub page QML file as per the current sub page type selected.
 *
 *  \author Vikas Pachdha
 *
 *  \return QString : Sub page QML file name.
 ******************************************************************************/
QString HelpPage_C::subPage() const
{
    QString sub_page = "";
    switch(_sub_page_type) {
    case GENERAL:
        sub_page = "General_help.qml";
        break;
    case RULES:
        sub_page = "Rules_help.qml";
        break;
    case SCORING:
        sub_page = "Scoring_help.qml";
        break;
    case OTHERS:
        sub_page = "Others_help.qml";
        break;
    default:
        break;
    }

    return sub_page;
}

//******************************************************************************
/*! \brief Sets sub page type.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] sub_page_type : New sub page type.
 ******************************************************************************/
void HelpPage_C::setSubPageType(const SubPage_TP &sub_page_type)
{
    if(_sub_page_type != sub_page_type) {
        LOG_INFO(QString("Help page :: Settings sub page %1").arg(sub_page_type));
        _sub_page_type = sub_page_type;
        emit subPageChanged();
    }
}
