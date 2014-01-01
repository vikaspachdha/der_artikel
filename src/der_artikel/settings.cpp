#include "settings.h"

Settings_C::Settings_C(QObject *parent) :
    QObject(parent),
    _current_language(ENGLISH)
{
}

void Settings_C::SetLanguage(Settings_C::Language_TP language)
{
    if(_current_language != language) {
        _current_language = language;
        emit LanguageChanged();
    }
}
