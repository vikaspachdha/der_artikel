#include "page.h"
#include "manager.h"
#include "log4qt/log_defines.h"

/********************************************************************************/
/** @brief Constructor\n
*   @sa CPage
*   @param[in]  pageId Page id of the page.
*   @param[in]  parent Parent instance for this instance of CImageArchivePage.
*********************************************************************************/
/*!
 \brief

 \param pageId
 \param page_manager
 \param parent
*/
Page_C::Page_C(Manager_C::PageId_TP page_id, Manager_C &page_manager, QObject *parent) :
    QObject(parent),
    _page_id(page_id),
    _page_manager(page_manager)
{
    LOG_DEBUG(QString("Page_C(PageId_TP %1)").arg(page_id));
}

/********************************************************************************/
/** @brief Returns the page id of the page.
*   @sa pageId
*   @return Manager_C::PageId_TP Page id of the page
*********************************************************************************/
/*!
 \brief

 \return Manager_C::PageId_TP
*/
Manager_C::PageId_TP Page_C::pageId() const
{
    return _page_id;
}


/********************************************************************************/
/** @brief \ref CPageManger calls this method to decide whether preconditions are
 *  met to enter this page. Override this method to define the preconditions for
 *  the corresponding page.
*   @sa canEnter
*   @return bool True i.e page can be switched.
*********************************************************************************/
/*!
 \brief

 \return bool
*/
bool Page_C::canEnter() const
{
    return true;
}

/********************************************************************************/
/** @brief \ref CPageManger calls this method to just before entering the page.
 *  Override this method to write initialization code for the corresponding page.
*   @sa enter
*********************************************************************************/
/*!
 \brief

 \param prev_page_id
*/
void Page_C::enter(Manager_C::PageId_TP prev_page_id)
{
    Q_UNUSED(prev_page_id)
}

/********************************************************************************/
/** @brief \ref CPageManger calls this method to decide whether conditions are
 *  met to leave this page. Override this method to define the conditions for
 *  the corresponding page.
*   @sa canLeave
*   @return bool True i.e page can be switched off.
*********************************************************************************/
/*!
 \brief

 \return bool
*/
bool Page_C::canLeave() const
{
    return true;
}

/********************************************************************************/
/** @brief \ref CPageManger calls this method to just after leaving the page.
 *  Override this method to write clean up code for the corresponding page.
*   @sa leave
*********************************************************************************/
/*!
 \brief

 \param next_page_id
*/
void Page_C::leave(Manager_C::PageId_TP next_page_id)
{
    Q_UNUSED(next_page_id)
}

/*!
 \brief

 \return QQuickItem
*/
QQuickItem *Page_C::titleItem()
{
    return _page_manager.titleItem(_page_id);
}

/*!
 \brief

 \return QQuickItem
*/
QQuickItem *Page_C::pageItem()
{
    return _page_manager.pageItem(_page_id);
}

/*!
 \brief

 \return QQuickItem
*/
QQuickItem *Page_C::panelItem()
{
    return _page_manager.panelItem(_page_id);
}
