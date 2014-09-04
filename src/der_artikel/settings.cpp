//******************************************************************************
/*! \file settings.cpp Implementation of \ref Settings_C
 *
 *  \author Vikas Pachdha
 *
 *  \copyright Copyright (C) 2014 Vikas Pachdha, Mohita Gandotra.
 * Contact: http://www.vikaspachdha.com
 *
 * This file is part of the application der_artikel.
 *
 *  \copyright GNU Lesser General Public License Usage
 * This file may be used under the terms of the GNU Lesser
 * General Public License version 2.1 as published by the Free Software
 * Foundation and appearing in the file LICENSE.LGPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU Lesser General Public License version 2.1 requirements
 * will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 *
 *  \copyright GNU General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 *
 ******************************************************************************/
// System includes
#include <QDate>
#include <QDir>
#include <QFileInfo>
#include <QSysInfo>
#include <QGuiApplication>
#include <QLocale>
#include <QQmlContext>
#include <QQmlComponent>
#include <QSettings>
#include <QStandardPaths>
#include <QTimer>
#include <QTranslator>

// Interface for this file
#include "settings.h"

// Framework and lib includes
#include "data/common.h"
#include "log4qt/log_defines.h"

// Project includes
#include "message_bar.h"

static const int MIN_WORD_MSG_TIME = 500; /*! Minimum time for info mode in word's page*/
static const int MAX_WORD_MSG_TIME = 5000; /*! Maximum time for info mode in word's page */
static const int MSG_ANIM_TIME = 400; /*! Message bar default animation time */


//******************************************************************************
/*! \brief Constructor.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] ref_qml_context : The root qml context.
 *  \param[in] parent : Parent object instance.
 ******************************************************************************/
Settings_C::Settings_C(QQmlContext &ref_qml_context, QObject *parent) :
    QObject(parent),
    _qml_context(ref_qml_context),
    _current_language(ENGLISH),
    _sound_level(0.1),
    _word_message_time(1200),
    _first_run(true),
    _thema_auto_update(true),
    _startup_thema_update(false),
    _color_palette(0),
    _mobile_platforms(false)
{
    LOG_DEBUG("Settings_C::constructor");
    LOG_INFO(QString("Platform : %1").arg(platformId()));

    if(platformId().contains("android") || platformId().contains("ios")) {
        _mobile_platforms = true;
    }

    // Setup UI demensions as per the platform.
    setupDimesions();

    QSettings::setDefaultFormat(QSettings::IniFormat);
    loadSettings();

    updateLangauge();
    _thema_remote_path = "vystosi.com/der_artikel/thema";

    // Create default thema dir.
    if(!QFileInfo::exists(defaultThemaDirPath())) {
        QDir themaRootDir;
        if(themaRootDir.mkpath(defaultThemaDirPath())) {
            // Set flag up as directory was not existing.
            _first_run = true;
        } else {
            LOG_ERROR("Cannot create default thema folder : " + defaultThemaDirPath());
        }
    }

#ifdef QT_DEBUG
    _first_run = true;
#endif

    if(_first_run || !_thema_auto_update_date.isValid()) {
        _startup_thema_update = true;
        _thema_auto_update_date = QDateTime::currentDateTime();
    } else {
        if(_thema_auto_update_date.daysTo(QDateTime::currentDateTime()) >=15 ) {
            _startup_thema_update = true;
            _thema_auto_update_date = QDateTime::currentDateTime();
        } else {
            _startup_thema_update = false;
        }
    }
}

//******************************************************************************
/*! \brief Destructor.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
Settings_C::~Settings_C()
{
    clearTranslators();
    saveSettings();
}

//******************************************************************************
/*! \brief Sets the language used for UI.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] language : New language selected.
 *
 *  \see \ref Settings_C::Language_TP
 ******************************************************************************/
void Settings_C::setLanguage(Settings_C::Language_TP language)
{
    if(_current_language != language) {
        LOG_INFO(QString("Language id changed to %1").arg(language));
        _current_language = language;
        updateLangauge();
        emit languageChanged();
    }
}

//******************************************************************************
/*! \brief Returns the class name of color palette instance.
 *
 *  \author Mohita Gandotra
 *
 *  \return Current color palette's class name. Empty string in case there is no
 *  color palette instantiated.
 *
 *  \see \ref Settings_C::colorPalette
 ******************************************************************************/
QString Settings_C::colorPaletteClass() const
{
    return _color_palette ? _color_palette->property("class_name").toString() : "";
}

//******************************************************************************
/*! \brief Sets the class name of the current color palette.
 *
 *  \brief The color palette instance is created if the class name is valid. Old
 *  color palette instance is deleted.
 *
 *  \author Mohita Gandotra
 *
 *  \param[in] class_name : Class name of the color palette.
 *
 *  \see \ref Settings_C::colorPalette
 ******************************************************************************/
void Settings_C::setColorPaletteClass(QString class_name)
{
    if(colorPaletteClass() != class_name) {
        QUrl color_palette_url(QString("qrc:/res/qml/der_artikel/%1.qml").arg(class_name));
        QQmlComponent color_palette_component(_qml_context.engine(),color_palette_url,&_qml_context);
        QObject* color_palette_instance = color_palette_component.create();
        QObject* old_color_palette_instance = _color_palette;
        if(color_palette_instance) {
             _color_palette = color_palette_instance;
             emit colorPaletteChanged();
             if(old_color_palette_instance) {
                 delete old_color_palette_instance;
             }
        }
    }
}

//******************************************************************************
/*! \brief Called when language is changed.Loads new translations as per the
 *  selected language.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
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

    clearTranslators();

    QDir lang_dir = ARTIKEL::GetResourcePath("languages");
    QStringList nameFilters;
    nameFilters<<"*.qm";

    QFileInfoList lang_files = lang_dir.entryInfoList(nameFilters,QDir::Files | QDir::NoSymLinks|QDir::NoDotAndDotDot);
    foreach(QFileInfo file, lang_files) {
        if(file.baseName().endsWith(language_code,Qt::CaseInsensitive)) {
            QTranslator* translator = new QTranslator;
            if(translator->load(file.absoluteFilePath())) {
                QGuiApplication::installTranslator(translator);
                _installed_translators<<translator;
            } else {
                delete translator;
            }
        }
    }

}

//******************************************************************************
/*! \brief Deletes and clear the installed translators.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void Settings_C::clearTranslators()
{
    foreach (QTranslator* translator, _installed_translators) {
        QGuiApplication::removeTranslator(translator);
        delete translator;
    }
    _installed_translators.clear();
}

void Settings_C::setupDimesions()
{
    if(_mobile_platforms) {
        // Frames
        _page_item_width =  128;
        _page_item_height = 158;
        _thema_item_width = 160;
        _thema_item_height = 160;
        _cmd_width = 82;
        _cmd_height = 82;
        _msg_bar_height = 130;
        _panel_frame_width= 160;
        _title_frame_height= 106;

        // Font sizes
        _title_text_size = 56;
        _heading_1_size=28;
        _heading_2_size=24;
        _cmd_text_size = 22;
        _sub_cmd_text_size = 16;
        _normal_text_size = 22;
        _noun_text_size = 36;
    } else {
        // Frames
        _page_item_width = 74;
        _page_item_height = 94;
        _thema_item_width = 104;
        _thema_item_height = 104;
        _cmd_width = 52;
        _cmd_height = 52;
        _msg_bar_height = 90;
        _panel_frame_width= 100;
        _title_frame_height= 76;

        // Font sizes
        _title_text_size = 42;
        _heading_1_size=16;
        _heading_2_size=14;
        _cmd_text_size = 14;
        _sub_cmd_text_size = 11;
        _normal_text_size = 14;
        _noun_text_size = 24;
    }
}

//******************************************************************************
/*! \brief Saves user settings to INI file.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void Settings_C::saveSettings()
{
    QSettings settings;
    settings.beginGroup("appSettings");
    settings.setValue("language",_current_language);
    settings.setValue("colorPalette",colorPaletteClass());
    settings.setValue("soundLevel",_sound_level);
    settings.setValue("wordMessageTime",_word_message_time);
    settings.setValue("remotePath",_thema_remote_path);
    settings.setValue("isFirstRun",false);
    settings.setValue("themaAutoUpdate",_thema_auto_update);
    settings.setValue("themaAutoUpdateDate",_thema_auto_update_date.isValid() ?
                          _thema_auto_update_date.toMSecsSinceEpoch() : -1);
    settings.endGroup();
}

//******************************************************************************
/*! \brief Loads user settings from INI file.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void Settings_C::loadSettings()
{
    QSettings settings;
    settings.beginGroup("appSettings");
    _current_language = (Language_TP)settings.value("language",ENGLISH).toInt();
    _sound_level = settings.value("soundLevel",0.1).toDouble();
    _word_message_time = settings.value("wordMessageTime",1200).toInt();
    _thema_remote_path = settings.value("remotePath","www.vystosi.com/der_artikel/themas").toString();
    _first_run = settings.value("isFirstRun",true).toBool();
    _thema_auto_update = settings.value("themaAutoUpdate",true).toBool();
    qint64 msecs = settings.value("themaAutoUpdateDate",-1).toLongLong();
    if(msecs > 0) {
        _thema_auto_update_date = QDateTime::fromMSecsSinceEpoch(msecs);
    }

    QString color_palette_class = settings.value("colorPalette","Color_palette_blue").toString();
    setColorPaletteClass(color_palette_class);

    settings.endGroup();
}

//******************************************************************************
/*! \brief Sets sound level.
 *
 *  \details Value range between 0 to 1, 0 being minimum and 1 being maximum.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] sound_level : New sound level.
 ******************************************************************************/
void Settings_C::setSoundLevel(double sound_level)
{
    if(qAbs(sound_level-_sound_level) > 0.001 ) {
        _sound_level = sound_level;
        emit soundLevelChanged();
    }
}

//******************************************************************************
/*! \brief Returns word message time string.
 *
 *  \details The string is used in UI.
 *
 *  \author Vikas Pachdha
 *
 *  \return QString : Word message time string.
 ******************************************************************************/
QString Settings_C::wordMsgTimeStr() const
{
    return QString::number(_word_message_time);
}

//******************************************************************************
/*! \brief Sets word message time string.
 *
 *  \details The string is used in UI.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] new_time_str : New word message time in msecs.
 ******************************************************************************/
void Settings_C::setWordMsgTimeStr(QString new_time_str)
{
    bool ok = false;
    int msecs = new_time_str.toInt(&ok);
    if(ok) {
        setWordMsgTime(msecs);
    }
}

//******************************************************************************
/*! \brief Sets word message time. Overrides default value.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] new_time : New word message time in msecs.
 ******************************************************************************/
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

//******************************************************************************
/*! \brief Minimimum time that can be set for info mode in word's page.
 *
 *  \author Vikas Pachdha
 *
 *  \return type : Minimum word message time in msecs.
 ******************************************************************************/
int Settings_C::minWordMsgTime() const
{
    return MIN_WORD_MSG_TIME;
}

//******************************************************************************
/*! \brief Maximimum time that can be set for info mode in word's page.
 *
 *  \author Vikas Pachdha
 *
 *  \return type : Maximum word message time in msecs.
 ******************************************************************************/
int Settings_C::maxWordMsgTime() const
{
    return MAX_WORD_MSG_TIME;
}

//******************************************************************************
/*! \brief Message animation time.
 *
 *  \author Vikas Pachdha
 *
 *  \return int : Animation time for message bar in msecs.
 ******************************************************************************/
int Settings_C::messageAnimTime() const
{
    return MSG_ANIM_TIME;
}

//******************************************************************************
/*! \brief Sets remote thema file's folder.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] url_str : Remote folder path.
 ******************************************************************************/
void Settings_C::setThemaRemotePath(QString url_str)
{
    if(url_str != _thema_remote_path) {
        LOG_INFO(QString("Remote thema folder path changed to %1").arg(url_str));
        _thema_remote_path = url_str;
        emit themaRemotePathChanged();
    }
}

//******************************************************************************
/*! \brief Returns local path to log file's folder.
 *
 *  \author Vikas Pachdha
 *
 *  \return QString : Local path to log file's folder.
 ******************************************************************************/
QString Settings_C::logsDirPath()
{
    return QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0) + "/logs";
}

//******************************************************************************
/*! \brief Returns local path to thema file's folder.
 *
 *  \author Vikas Pachdha
 *
 *  \return QString : Local path to thema file's folder.
 ******************************************************************************/
QString Settings_C::defaultThemaDirPath()
{
    return QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0) + "/themas";
}

//******************************************************************************
/*! \brief Sets thema auto update. When enabled thema file update is triggered on
 *         every 15th of the month.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] auto_update : True to enable thema update, false otherwise.
 ******************************************************************************/
void Settings_C::setThemaAutoUpdate(bool auto_update)
{
    if(auto_update) {
        LOG_INFO("Enabling thema auto update");
        _thema_auto_update = true;
        emit themaAutoUpdateChanged();
    } else {
        if(_thema_auto_update) {
            // https://bugreports.qt-project.org/browse/QTBUG-38729
            QTimer::singleShot(0,this,SLOT(disableThemaAutoUpdate()));
        }
    }
}

//******************************************************************************
/*! \brief Slot to disable auto update.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void Settings_C::disableThemaAutoUpdate()
{
    LOG_INFO("Disabling thema auto update");
    if( MessageBar_C::showMsg(tr("Do you really want to disable the thema update?"),"") == MessageBar_C::ACCEPTED) {
        _thema_auto_update = false;
        emit themaAutoUpdateChanged();
    }
}

//******************************************************************************
/*! \brief Returns the platform id.
 *
 *  \author Vikas Pachdha
 *
 *  \return QString : The platform id.
 ******************************************************************************/
QString Settings_C::platformId() const
{
    QString id;

#ifdef Q_OS_WIN32
    id = "windows_32";
#endif

#ifdef Q_OS_WIN64
    id = "windows_64";
#endif

#ifdef Q_OS_MAC64
    if(QSysInfo::macVersion() == QSysInfo::MV_10_9) {
        id = "osx_10.9";
    } else if(QSysInfo::macVersion() == QSysInfo::MV_10_8) {
        id = "osx_10.8";
    } else if(QSysInfo::macVersion() == QSysInfo::MV_10_7) {
        id = "osx_10.7";
    }else if(QSysInfo::macVersion() == QSysInfo::MV_10_6) {
        id = "osx_10.6";
    }
#endif

#ifdef Q_OS_LINUX
    #ifdef Q_PROCESSOR_X86_32
        id = "linux_x86";
    #endif
    #ifdef Q_PROCESSOR_X86_64
        id = "linux_x86_64";
    #endif
#endif

#ifdef Q_OS_ANDROID
    #ifdef Q_PROCESSOR_ARM_V5
        id = "android_arm_5";
    #endif
    #ifdef Q_PROCESSOR_ARM_V6
        id = "android_arm_6";
    #endif
    #ifdef Q_PROCESSOR_ARM_V7
        id = "android_arm_7";
    #endif
    #ifdef Q_PROCESSOR_X86_32
        id = "android_x86";
    #endif
#endif

#ifdef Q_OS_IOS
    id = "ios";
#endif

        return id;
}


