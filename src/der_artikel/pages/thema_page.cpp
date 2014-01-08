#include "thema_page.h"
#include "thema_model.h"

ThemaPage_C::ThemaPage_C(Manager_C &page_manager, QObject *parent) :
    Page_C(Manager_C::THEMA_PAGE, page_manager, parent)
{

}

void ThemaPage_C::enter()
{
    _page_manager.GetThemaModel()->ClearSelection();
}

void ThemaPage_C::leave()
{

}
