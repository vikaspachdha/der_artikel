#ifndef PAGE_I_H
#define PAGE_I_H

#include "manager.h"
#include <QList>
#include <QString>

/** @brief Interface class for a Page entity. \ref CPageManager manages the pages using this interface.
 *
 */
/**
 * @brief
 *
 */
class Page_I
{
public:
/**
 * @brief
 *
 */
    Page_I() {}
    /**
     * @brief
     *
     */
    virtual ~Page_I() {}

public:
    /********************************************************************************/
    /** @brief Returns the page id of the page.
    *   @sa pageId
    *   @return Manager_C::PageId_TP Page id of the page
    *********************************************************************************/
    /**
     * @brief
     *
     * @return Manager_C::PageId_TP
     */
    virtual Manager_C::PageId_TP pageId() const = 0;

    /********************************************************************************/
    /** @brief \ref CPageManger calls this method to decide whether preconditions are
     *  met to enter this page. Implement this method to define the preconditions for
     *  the corresponding page.
    *   @sa canEnter
    *   @return bool True if page can be switched. False otherwise
    *********************************************************************************/
    /**
     * @brief
     *
     * @return bool
     */
    virtual bool canEnter() const = 0;

    /********************************************************************************/
    /** @brief \ref CPageManger calls this method to just before entering the page.
     *  Implement this method to write initialization code for the corresponding page.
    *   @sa enter
    *********************************************************************************/
    /**
     * @brief
     *
     * @param prev_page_id
     */
    virtual void enter(Manager_C::PageId_TP prev_page_id) = 0;

    /********************************************************************************/
    /** @brief \ref CPageManger calls this method to decide whether conditions are
     *  met to leave this page. Implement this method to define the conditions for
     *  the corresponding page.
    *   @sa canLeave
    *   @return bool True if page can be switched off. False otherwise
    *********************************************************************************/
    /**
     * @brief
     *
     * @return bool
     */
    virtual bool canLeave() const = 0;

    /********************************************************************************/
    /** @brief \ref CPageManger calls this method to just after leaving the page.
     *  Implement this method to write clean up code for the corresponding page.
    *   @sa leave
    *********************************************************************************/
    /**
     * @brief
     *
     * @param next_page_id
     */
    virtual void leave(Manager_C::PageId_TP next_page_id) = 0;
};

#endif // IPAGE_H
