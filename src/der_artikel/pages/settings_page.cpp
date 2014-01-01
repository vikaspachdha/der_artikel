#include "settings_page.h"
#include <QQmlContext>

SettingsPage_C::SettingsPage_C(Manager_C& page_manager,QQmlContext &root_context, QObject *parent) :
    Page_C(Manager_C::SETTINGS_PAGE, page_manager, parent),
    _root_context(root_context),
    _sub_page_type(LANGUAGE)
{
    _root_context.setContextProperty("settings_page_instance",this);
}

void SettingsPage_C::enter()
{
    setSubPageType(LANGUAGE);
}

QString SettingsPage_C::title() const
{
    QString title = "";
    switch(_sub_page_type) {
    case LANGUAGE:
        title = tr("Language settings");
        break;
    case SOUND:
        title = tr("Sound settings");
        break;
    case COLOR_THEME:
        title = tr("Color theme settings");
        break;
    case GAME_PLAY:
        title = tr("Game Play Settings");
        break;
    default:
        break;
    }

    return title;
}

QString SettingsPage_C::subPage() const
{
    QString sub_page = "";
    switch(_sub_page_type) {
    case LANGUAGE:
        sub_page = tr("Language_settings.qml");
        break;
    case SOUND:
        sub_page = tr("Sound_settings.qml");
        break;
    case COLOR_THEME:
        sub_page = tr("Color_theme_settings.qml");
        break;
    case GAME_PLAY:
        sub_page = tr("Game_play_settings.qml");
        break;
    default:
        break;
    }

    return sub_page;
}

void SettingsPage_C::setSubPageType(const SubPage_TP &sub_page_type)
{
    if(_sub_page_type != sub_page_type) {
        _sub_page_type = sub_page_type;
        emit subPageChanged();
    }
}
