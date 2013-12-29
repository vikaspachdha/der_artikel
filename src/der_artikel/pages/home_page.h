#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include "page.h"
/** @brief Entity class for dashboard page. The entity defines menu items for the
 *  dashboard page and how to use the shared user interface elements such as menu and
 *  status bar.
 */
class HomePage_C : public Page_C
{
    Q_OBJECT
public:
    explicit HomePage_C(Manager_C& page_manager, QQmlContext& root_context,QObject *parent = 0);

private:
    QQmlContext& _root_context;
};

#endif // HOMEPAGE_H
