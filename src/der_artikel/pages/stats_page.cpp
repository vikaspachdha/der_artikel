#include "stats_page.h"
#include <QQuickItem>

/*!
 \brief

 \param page_manager
 \param root_context
 \param parent
*/
StatsPage_C::StatsPage_C(Manager_C &page_manager, QQmlContext &root_context, QObject *parent) :
    Page_C(Manager_C::STATS_PAGE, page_manager, parent),
    _root_context(root_context)
{
}

/*!
 \brief

 \param prev_page_id
*/
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
