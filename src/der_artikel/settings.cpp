#include "settings.h"
#include <QLocale>
#include <QTranslator>
#include <QApplication>
#include <QDir>
#include <QDebug>
#include "common.h"

Settings_C::Settings_C(QObject *parent) :
    QObject(parent),
    _current_language(ENGLISH),
    _sound_level(0.1)
{
    updateLangauge();
}

void Settings_C::SetLanguage(Settings_C::Language_TP language)
{
    if(_current_language != language) {
        _current_language = language;
        updateLangauge();
        emit LanguageChanged();
    }
}

void Settings_C::updateLangauge()
{
    QString language_code = "en";
    switch( _current_language ) {
    case GERMAN:
        QLocale::setDefault(QLocale::German);
        language_code = "de";
        break;
    case HINDI:
        QLocale::setDefault(QLocale::Hindi);
        language_code = "hin";
        break;
    default:
        QLocale::setDefault(QLocale::English);
        break;
    }

    foreach (QTranslator* translator, _installed_translators) {
        QApplication::removeTranslator(translator);
        delete translator;
    }
    _installed_translators.clear();

    QDir lang_dir = ARTIKEL::GetResourcePath("languages");
    QStringList nameFilters;
    nameFilters<<"*.qm";

    QFileInfoList lang_files = lang_dir.entryInfoList(nameFilters,QDir::Files | QDir::NoSymLinks|QDir::NoDotAndDotDot);
    foreach(QFileInfo file, lang_files) {
        if(file.baseName().endsWith(language_code,Qt::CaseInsensitive)) {
            QTranslator* translator = new QTranslator;
            if(translator->load(file.absoluteFilePath())) {
                QApplication::installTranslator(translator);
                _installed_translators<<translator;
                qDebug()<<"Transalation loaded "<<file.absoluteFilePath();
            } else {
                qDebug()<<"Transalation load failed "<<file.absoluteFilePath();
            }
        }
    }

}

void Settings_C::setSoundLevel(double sound_level)
{
    if(qAbs(sound_level-_sound_level) > 0.001 ) {
        _sound_level = sound_level;
        emit soundLevelChanged();
    }
}

