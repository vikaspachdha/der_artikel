#ifndef WORDS_PAGE_H
#define WORDS_PAGE_H

#include "page.h"

class WordsPage_C : public Page_C
{
    Q_OBJECT
public:
    explicit WordsPage_C(Manager_C& page_manager, QQmlContext& root_context, QObject *parent = 0);

public:
    virtual void enter();
    virtual void leave();

private:
    QQmlContext& _root_context;
};

#endif // WORDS_PAGE_H
