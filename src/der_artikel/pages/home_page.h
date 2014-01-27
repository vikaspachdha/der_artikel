#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include "page.h"

/**
 * @brief
 *
 */
class HomePage_C : public Page_C
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
    explicit HomePage_C(Manager_C& page_manager, QQmlContext& root_context,QObject *parent = 0);

private:
    QQmlContext& _root_context; /**< TODO */
};

#endif // HOMEPAGE_H
