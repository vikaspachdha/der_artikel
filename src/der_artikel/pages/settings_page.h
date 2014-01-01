#ifndef SETTINGS_PAGE_H
#define SETTINGS_PAGE_H

#include "page.h"
/** @brief Entity class for settings page. The entity defines menu items for the
 *  settings page and how to use the shared user interface elements such as menu and
 *  status bar.
 */
class SettingsPage_C : public Page_C
{
    Q_OBJECT
    Q_PROPERTY(QString sub_page READ subPage NOTIFY subPageChanged)
    Q_PROPERTY(SubPage_TP sub_page_type READ subPageType WRITE setSubPageType NOTIFY subPageChanged)
    Q_PROPERTY(QString title READ title NOTIFY subPageChanged)

    Q_ENUMS(SubPage_TP)
public:
    enum SubPage_TP {
        LANGUAGE=1,
        SOUND,
        COLOR_THEME,
        GAME_PLAY
    };

public:
    explicit SettingsPage_C(Manager_C& page_manager, QQmlContext& root_context, QObject *parent = 0);

public:
    virtual void enter();

public:

    QString title() const;

    QString subPage() const;

    SubPage_TP subPageType() const { return _sub_page_type; }
    void setSubPageType(const SubPage_TP &sub_page_type);

signals:
    void subPageChanged();

private:
    QQmlContext& _root_context;
    SubPage_TP _sub_page_type;
};

#endif // SETTINGSPAGE_H
