/********************************************************************************/
/** @file   Page.h
*   @brief  Declaration of the CPage class
*   @par    Erstellt von:
*               Vikas Pachdha
*   @par    Erstellungsdatum:
*               19 Dezember 2013
*   @par    Copyright:
*               Copyright (c) 2011 e-GITS GmbH
*********************************************************************************/
#ifndef PAGE_H
#define PAGE_H

#include <QObject>
#include "page_i.h"

/** @brief Abstract class for a Page entity. Implements the IPage interface with defaults
 *
 */
class Page_C : public QObject, public Page_I
{
    Q_OBJECT

public:
    explicit Page_C(Manager_C::PageId_TP pageId, Manager_C& page_manager, QObject *parent = 0);

public:
    virtual Manager_C::PageId_TP pageId() const;
    virtual bool canEnter() const;
    virtual void enter();
    virtual bool canLeave() const;
    virtual void leave();

protected:
    QQuickItem* titleItem();
    QQuickItem* pageItem();
    QQuickItem* panelItem();

protected:
    Manager_C::PageId_TP _page_id;
    Manager_C& _page_manager;
};

#endif // PAGE_H
