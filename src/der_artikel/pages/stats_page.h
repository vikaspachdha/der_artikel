#ifndef STATS_PAGE_H
#define STATS_PAGE_H
#include "page.h"

class StatsPage_C : public Page_C
{
    Q_OBJECT
public:
    explicit StatsPage_C(Manager_C& page_manager, QQmlContext& root_context, QObject *parent = 0);

public:
    virtual void enter();

private:
    QQmlContext& _root_context;

};

#endif // STATS_PAGE_H
