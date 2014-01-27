#ifndef STATS_PAGE_H
#define STATS_PAGE_H
#include "page.h"

/**
 * @brief
 *
 */
class StatsPage_C : public Page_C
{
    Q_OBJECT
public:
    /**
     * @brief
     *
     * @param page_manager
     * @param root_context
     * @param parent
     */
    explicit StatsPage_C(Manager_C& page_manager, QQmlContext& root_context, QObject *parent = 0);

public:
    /**
     * @brief
     *
     * @param prev_page_id
     */
    virtual void enter(Manager_C::PageId_TP prev_page_id);

private:
    QQmlContext& _root_context; /**< TODO */

};

#endif // STATS_PAGE_H
