#ifndef SETTINGS_PAGE_H
#define SETTINGS_PAGE_H

#include "page.h"
/** @brief Entity class for settings page. The entity defines menu items for the
 *  settings page and how to use the shared user interface elements such as menu and
 *  status bar.
 */
/**
 * @brief
 *
 */
class SettingsPage_C : public Page_C
{
    Q_OBJECT
    Q_PROPERTY(QString sub_page READ subPage NOTIFY subPageChanged)
    Q_PROPERTY(SubPage_TP sub_page_type READ subPageType WRITE setSubPageType NOTIFY subPageChanged)
    Q_PROPERTY(QString title READ title NOTIFY subPageChanged)

    Q_ENUMS(SubPage_TP)
public:
    /**
     * @brief
     *
     */
    enum SubPage_TP {
        LANGUAGE=1,
        SOUND,
        COLOR_THEME,
        GAME_PLAY
    };

public:
    /**
     * @brief
     *
     * @param page_manager
     * @param root_context
     * @param parent
     */
    explicit SettingsPage_C(Manager_C& page_manager, QQmlContext& root_context, QObject *parent = 0);

public:
    /**
     * @brief
     *
     * @param prev_page_id
     */
    virtual void enter(Manager_C::PageId_TP prev_page_id);

public:

    /**
     * @brief
     *
     * @return QString
     */
    QString title() const;

    /**
     * @brief
     *
     * @return QString
     */
    QString subPage() const;

    /**
     * @brief
     *
     * @return SubPage_TP
     */
    SubPage_TP subPageType() const { return _sub_page_type; }
    /**
     * @brief
     *
     * @param sub_page_type
     */
    void setSubPageType(const SubPage_TP &sub_page_type);

signals:
    /**
     * @brief
     *
     */
    void subPageChanged();

private:
    QQmlContext& _root_context; /**< TODO */
    SubPage_TP _sub_page_type; /**< TODO */
};

#endif // SETTINGSPAGE_H
