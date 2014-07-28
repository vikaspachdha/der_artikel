#ifndef ABOUT_PAGE_H
#define ABOUT_PAGE_H

// Project includes
#include "page.h"

// Forward declaration
class QQmlContext;


//******************************************************************************
/*! \brief Entity class for about page. The entity defines menu items for the
 *  about page and how to use the shared user interface elements such as menu and
 *  status bar.
 *
 *  \details User is provided with application information.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
class AboutPage_C : public Page_C
{
    Q_OBJECT
    Q_PROPERTY(QString sub_page READ subPage NOTIFY subPageChanged)
    Q_PROPERTY(SubPage_TP sub_page_type READ subPageType WRITE setSubPageType NOTIFY subPageChanged)
    Q_PROPERTY(QString license_text READ licenseText CONSTANT)

    Q_ENUMS(SubPage_TP)

public:
    //! Sub pages within help page.
    enum SubPage_TP {
        ABOUT=1,
        LICENSE
    };

public:
    explicit AboutPage_C(Manager_C& page_manager, QQmlContext& root_context, QObject *parent = 0);

public:
    virtual void enter(Manager_C::PageId_TP prev_page_id);

public:
    QString subPage() const;

    QString licenseText() const;

    //! Returns the current selected sub page.
    SubPage_TP subPageType() const { return _sub_page_type; }
    void setSubPageType(const SubPage_TP &sub_page_type);

signals:
    //! Emitted when sub page changes.
    void subPageChanged();

private:
    //! Root QML context instance.
    QQmlContext& _root_context;
    //! Sub page.
    SubPage_TP _sub_page_type;
    //! License text.
    QString _license_text;
};
#endif // ABOUT_PAGE_H
