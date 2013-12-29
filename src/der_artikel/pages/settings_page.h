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
public:
    explicit SettingsPage_C(Manager_C& refPageManager, QObject *parent = 0);
};

#endif // SETTINGSPAGE_H
