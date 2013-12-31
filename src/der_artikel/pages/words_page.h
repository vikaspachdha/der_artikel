#ifndef WORDS_PAGE_H
#define WORDS_PAGE_H

#include "page.h"

class WordsPage_C : public Page_C
{
    Q_OBJECT
    Q_PROPERTY(bool info_mode READ infoMode WRITE setInfoMode NOTIFY infoModeChanged)

public:
    explicit WordsPage_C(Manager_C& page_manager, QQmlContext& root_context, QObject *parent = 0);

public:
    virtual void enter();
    virtual void leave();

public:
    bool infoMode() const { return _info_mode; }
    void setInfoMode(bool info_mode);

signals:
    void infoModeChanged();

private:
    QQmlContext& _root_context;
    bool _info_mode;
};

#endif // WORDS_PAGE_H
