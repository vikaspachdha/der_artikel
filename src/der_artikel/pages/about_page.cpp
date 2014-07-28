//******************************************************************************
/*! \file about_page.cpp Implementation of \ref AboutPage_C
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
#include <QFile>
#include <QQmlContext>

// Interface for this file
#include "about_page.h"

// Framework and lib includes
#include "log4qt/log_defines.h"


//******************************************************************************
/*! \brief Constructor
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] page_manager : \ref CPageManager_C instance.
 *  \param[in] root_context : QML root context instance.
 *  \param[in] parent : Parent instance.
 ******************************************************************************/
AboutPage_C::AboutPage_C(Manager_C& page_manager,QQmlContext &root_context, QObject *parent) :
    Page_C(Manager_C::ABOUT_PAGE, page_manager, parent),
    _root_context(root_context),
    _sub_page_type(ABOUT)
{
    _root_context.setContextProperty("about_page_instance",this);

    QFile license_file(":/res/resources/license.txt");
    if(license_file.open(QIODevice::ReadOnly)) {
        _license_text = license_file.readAll();
    } else {
        _license_text = tr("License file is unavailable.");
    }
}

//******************************************************************************
/*! \brief Called when page enters. Default sub page "About" is set.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] prev_page_id : Previous page id.
 ******************************************************************************/
void AboutPage_C::enter(Manager_C::PageId_TP prev_page_id)
{
    Q_UNUSED(prev_page_id)
    setSubPageType(ABOUT);
}

//******************************************************************************
/*! \brief Returns sub page QML file as per the current sub page type selected.
 *
 *  \author Vikas Pachdha
 *
 *  \return QString : Sub page QML file name.
 ******************************************************************************/
QString AboutPage_C::subPage() const
{
    QString title = "";
    switch(_sub_page_type) {
    case ABOUT:
        title = "About.qml";
        break;
    case LICENSE:
        title = "License.qml";
        break;
    default:
        break;
    }

    return title;
}

//******************************************************************************
/*! \brief Returns license text.
 *
 *  \author Vikas Pachdha
 *
 *  \return QString : License text.
 ******************************************************************************/
QString AboutPage_C::licenseText() const
{
    return _license_text;
}

//******************************************************************************
/*! \brief Sets sub page type.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] sub_page_type : New sub page type.
 ******************************************************************************/
void AboutPage_C::setSubPageType(const SubPage_TP &sub_page_type)
{
    if(_sub_page_type != sub_page_type) {
        LOG_INFO(QString("About page :: Setting sub page %1").arg(sub_page_type));
        _sub_page_type = sub_page_type;
        emit subPageChanged();
    }
}
