#ifndef THEMA_PAGE_H
#define THEMA_PAGE_H

#include "page.h"

class ThemaPage_C : public Page_C
{
    Q_OBJECT
public:
    explicit ThemaPage_C(Manager_C& page_manager, QObject *parent = 0);

public:
    virtual void enter();
    virtual void leave();

};

#endif // THEMA_PAGE_H
