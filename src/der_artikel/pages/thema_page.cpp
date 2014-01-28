#include "thema_page.h"
#include "thema_model.h"

/*!
 \brief

 \param page_manager
 \param parent
*/
ThemaPage_C::ThemaPage_C(Manager_C &page_manager, QObject *parent) :
    Page_C(Manager_C::THEMA_PAGE, page_manager, parent)
{

}

/*!
 \brief

 \param prev_page_id
*/
void ThemaPage_C::enter(Manager_C::PageId_TP prev_page_id)
{
    Q_UNUSED(prev_page_id)
    _page_manager.GetThemaModel()->ClearSelection();
}

/*!
 \brief

 \param next_page_id
*/
void ThemaPage_C::leave(Manager_C::PageId_TP next_page_id)
{
    Q_UNUSED(next_page_id)
}
