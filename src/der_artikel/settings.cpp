#include "settings.h"
#include <QLocale>
#include <QTranslator>
#include <QApplication>
#include <QDir>
#include <QDebug>
#include "common.h"

static const int MIN_WORD_MSG_TIME = 500; /*!< TODO */
static const int MAX_WORD_MSG_TIME = 5000; /*!< TODO */

/*!
 \brief

 \param parent
*/
Settings_C::Settings_C(QObject *parent) :
    QObject(parent),
    _current_language(ENGLISH),
    _sound_level(0.1),
    _word_message_time(1200)
{
    updateLangauge();
    _thema_update_url_str = "www.vikaspachdha.com/der_artikel_data";
}

/*!
 \brief

 \param language
*/
void Settings_C::SetLanguage(Settings_C::Language_TP language)
{
    if(_current_language != language) {
        _current_language = language;
        updateLangauge();
        emit LanguageChanged();
    }
}

/*!
 \brief

*/
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
            }
        }
    }

}

/*!
 \brief

 \param sound_level
*/
void Settings_C::setSoundLevel(double sound_level)
{
    if(qAbs(sound_level-_sound_level) > 0.001 ) {
        _sound_level = sound_level;
        emit soundLevelChanged();
    }
}

/*!
 \brief

 \return QString
*/
QString Settings_C::wordMsgTimeStr() const
{
    return QString::number(_word_message_time);
}

/*!
 \brief

 \param new_time_str
*/
void Settings_C::setWordMsgTimeStr(QString new_time_str)
{
    bool ok = false;
    int msecs = new_time_str.toInt(&ok);
    if(ok) {
        setWordMsgTime(msecs);
    }
}

/*!
 \brief

 \param new_time
*/
void Settings_C::setWordMsgTime(int new_time)
{
    if(new_time < 500) {
        new_time = 500;
    }
    if(new_time > 5000) {
        new_time = 5000;
    }
    if(_word_message_time != new_time) {
        _word_message_time = new_time;
        emit wordMsgTimeChanged();
    }
}

/*!
 \brief

 \return int
*/
int Settings_C::minWordMsgTime() const
{
    return MIN_WORD_MSG_TIME;
}

/*!
 \brief

 \return int
*/
int Settings_C::maxWordMsgTime() const
{
    return MAX_WORD_MSG_TIME;
}

/*!
 \brief

 \param url_str
*/
void Settings_C::setThemaUpdateUrl(QUrl url_str)
{
    if(url_str != _thema_update_url_str) {
        _thema_update_url_str = url_str;
        emit themaUpdateUrlChanged();
    }
}

