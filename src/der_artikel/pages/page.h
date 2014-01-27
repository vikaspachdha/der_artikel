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
/**
 * @brief
 *
 */
class Page_C : public QObject, public Page_I
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param pageId
     * @param page_manager
     * @param parent
     */
    explicit Page_C(Manager_C::PageId_TP pageId, Manager_C& page_manager, QObject *parent = 0);

public:
    /**
     * @brief
     *
     * @return Manager_C::PageId_TP
     */
    virtual Manager_C::PageId_TP pageId() const;
    /**
     * @brief
     *
     * @return bool
     */
    virtual bool canEnter() const;
    /**
     * @brief
     *
     * @param prev_page_id
     */
    virtual void enter(Manager_C::PageId_TP prev_page_id);
    /**
     * @brief
     *
     * @return bool
     */
    virtual bool canLeave() const;
    /**
     * @brief
     *
     * @param next_page_id
     */
    virtual void leave(Manager_C::PageId_TP next_page_id);

protected:
    /**
     * @brief
     *
     * @return QQuickItem
     */
    QQuickItem* titleItem();
    /**
     * @brief
     *
     * @return QQuickItem
     */
    QQuickItem* pageItem();
    /**
     * @brief
     *
     * @return QQuickItem
     */
    QQuickItem* panelItem();

protected:
    Manager_C::PageId_TP _page_id; /**< TODO */
    Manager_C& _page_manager; /**< TODO */
};

#endif // PAGE_H
