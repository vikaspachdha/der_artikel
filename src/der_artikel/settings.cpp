#include "settings.h"

Settings_C::Settings_C(QObject *parent) :
    QObject(parent),
    _current_language(ENGLISH),
    _sound_level(0.1)
{
}

void Settings_C::SetLanguage(Settings_C::Language_TP language)
{
    if(_current_language != language) {
        _current_language = language;
        emit LanguageChanged();
    }
}

void Settings_C::setSoundLevel(double sound_level)
{
    if(qAbs(sound_level-_sound_level) > 0.001 ) {
        _sound_level = sound_level;
        emit soundLevelChanged();
    }
}
