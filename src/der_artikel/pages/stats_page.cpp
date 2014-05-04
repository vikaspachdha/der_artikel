//******************************************************************************
/*! \file stats_page.cpp Implementation of \ref StatsPage_C
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
#include <QQuickItem>

// Interface for this file
#include "stats_page.h"


//******************************************************************************
/*! \brief Constructor
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] page_manager : \ref CPageManager_C instance.
 *  \param[in] root_context : QML root context instance.
 *  \param[in] parent : Parent instance.
 ******************************************************************************/
StatsPage_C::StatsPage_C(Manager_C &page_manager, QQmlContext &root_context, QObject *parent) :
    Page_C(Manager_C::STATS_PAGE, page_manager, parent),
    _root_context(root_context)
{
}

//******************************************************************************
/*! \brief Called when page enters. Statistics are generated
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] prev_page_id : Previous page id.
 ******************************************************************************/
void StatsPage_C::enter(Manager_C::PageId_TP prev_page_id)
{
    Q_UNUSED(prev_page_id)
    ThemaModel_C* thema_model = _page_manager.GetThemaModel();
    Q_ASSERT(thema_model);
    int thema_count = thema_model->rowCount();
    int rusty_thema_count = 0;
    int silver_thema_count = 0;
    int gold_thema_count = 0;
    int inert_thema_count = 0;
    int best_score = 0;
    QString best_thema = tr("None");
    for(int index=0; index < thema_count;++index) {
        Thema_C::State_TP thema_state =(Thema_C::State_TP) thema_model->data(thema_model->index(index,0), ThemaModel_C::THEMA_STATE).toInt();

        switch(thema_state) {
        case Thema_C::SILVER:
            ++silver_thema_count;
            break;
        case Thema_C::GOLD:
            ++gold_thema_count;
            break;
        case Thema_C::INERT:
            ++inert_thema_count;
            break;
        default:
            ++rusty_thema_count;
            break;
        }
        int experience = thema_model->data(thema_model->index(index,0), ThemaModel_C::EXPERIENCE).toInt();
        if(experience > best_score) {
            best_score = experience;
            best_thema = thema_model->data(thema_model->index(index,0), ThemaModel_C::DISPLAY_NAME).toString();
        }
    }

    QQuickItem* page_item = pageItem();
    if(page_item) {
        page_item->setProperty("thema_count",thema_count);
        page_item->setProperty("inert_thema_count",inert_thema_count);
        page_item->setProperty("golden_thema_count",gold_thema_count);
        page_item->setProperty("silver_thema_count",silver_thema_count);
        page_item->setProperty("rusty_thema_count",rusty_thema_count);
        page_item->setProperty("best_thema_name",best_thema);
    }

}
