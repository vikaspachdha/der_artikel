//******************************************************************************
/*! \file settings.h Declaration of \ref Settings_C
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
#ifndef SETTINGS_H
#define SETTINGS_H

// System includes
#include <QObject>
#include <QDateTime>
#include <QHash>
#include <QUrl>

// Forward declaration
class QTranslator;
class QQmlContext;

//******************************************************************************
/*! \brief Application settings.
 *
 *  \details Settings are serialized and loaded on application start.
 *
 *  \author Vikas Pachdha
 *
 *  \todo Create template settings like silent, custom and loud.
 *  \todo Sound levels not working.
 ******************************************************************************/
class Settings_C : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Language_TP language READ language WRITE setLanguage NOTIFY languageChanged)
    Q_PROPERTY(QObject* color_palette READ colorPalette NOTIFY colorPaletteChanged)
    Q_PROPERTY(QString color_palette_class READ colorPaletteClass WRITE setColorPaletteClass NOTIFY colorPaletteChanged)
    Q_PROPERTY(QString i18n_empty_string READ i18EmptyString NOTIFY languageChanged)
    Q_PROPERTY(double sound_level READ soundLevel WRITE setSoundLevel NOTIFY soundLevelChanged)
    Q_PROPERTY(QString word_msg_time_str READ wordMsgTimeStr WRITE setWordMsgTimeStr NOTIFY wordMsgTimeChanged)
    Q_PROPERTY(int word_msg_time READ wordMsgTime WRITE setWordMsgTime NOTIFY wordMsgTimeChanged)
    Q_PROPERTY(int min_word_msg_time READ minWordMsgTime CONSTANT)
    Q_PROPERTY(int max_word_msg_time READ maxWordMsgTime CONSTANT)
    Q_PROPERTY(int message_anim_time READ messageAnimTime CONSTANT)
    Q_PROPERTY(QString thema_remote_path READ themaRemotePath WRITE setThemaRemotePath NOTIFY themaRemotePathChanged)
    Q_PROPERTY(bool thema_auto_update READ themaAutoUpdate WRITE setThemaAutoUpdate NOTIFY themaAutoUpdateChanged)
    Q_PROPERTY(bool startup_thema_update READ startupThemaUpdate CONSTANT)

    Q_PROPERTY(int title_text_size READ titleTextSize  CONSTANT)
    Q_PROPERTY(int heading_1_size READ heading1Size  CONSTANT)
    Q_PROPERTY(int heading_2_size READ heading2Size CONSTANT)
    Q_PROPERTY(int cmd_text_size READ cmdTextSize CONSTANT)
    Q_PROPERTY(int sub_cmd_text_size READ subCmdTextSize CONSTANT)
    Q_PROPERTY(int normal_text_size READ normalTextSize CONSTANT)
    Q_PROPERTY(int noun_text_size READ nounTextSize CONSTANT)
    Q_PROPERTY(qreal page_item_width READ pageItemWidth CONSTANT)
    Q_PROPERTY(qreal page_item_height READ pageItemHeight CONSTANT)
    Q_PROPERTY(qreal thema_item_width READ themaItemWidth CONSTANT)
    Q_PROPERTY(qreal thema_item_height READ themaItemHeight CONSTANT)
    Q_PROPERTY(qreal cmd_width READ cmdWidth CONSTANT)
    Q_PROPERTY(qreal cmd_height READ cmdHeight CONSTANT)
    Q_PROPERTY(qreal msg_bar_height READ msgBarHeight CONSTANT)
    Q_PROPERTY(qreal panel_frame_width READ panelFrameWidth CONSTANT)
    Q_PROPERTY(qreal title_frame_height READ titleFrameHeight CONSTANT)
    Q_ENUMS(Language_TP)

public:

    //! UI languages.
    enum Language_TP {
        INVALID_LANGUAGE,
        ENGLISH,
        GERMAN,
        HINDI
    };

public:
    explicit Settings_C(QQmlContext& ref_qml_context, QObject *parent = 0);
    ~Settings_C();

public:

    //! Returns current language selected.
    Language_TP language() const { return _current_language; }
    void setLanguage(Language_TP language);

    //! Returns the color palette instance.
    QObject* colorPalette() const { return _color_palette; }

    QString colorPaletteClass() const;
    void setColorPaletteClass(QString class_name);

    //! Current sound level.
    double soundLevel() const { return _sound_level; }
    void setSoundLevel(double sound_level);

    QString wordMsgTimeStr() const;
    void setWordMsgTimeStr(QString new_time_str);

    //! Message time for info mode in Word's page.
    int wordMsgTime() const {return _word_message_time; }
    void setWordMsgTime(int new_time);

    int minWordMsgTime() const;
    int maxWordMsgTime() const;

    int messageAnimTime() const;

    //! Remote server path for updating thema files.
    QString themaRemotePath() const { return _thema_remote_path; }
    void setThemaRemotePath(QString url_str);

    static QString logsDirPath();

    static QString defaultThemaDirPath();

    //! Remote server path for updating app.
    QString versionInfoPath() const { return "www.vystosi.com/version_info.xml"; }

    //! Copy stock thema flag.
    bool isFirstRun() const { return _first_run; }

    void setThemaAutoUpdate(bool auto_update);
    //! Thema auto update flag.
    bool themaAutoUpdate() const { return _thema_auto_update; }

    bool startupThemaUpdate() const { return _startup_thema_update; }

    QString platformId() const;

    int titleTextSize() const { return _title_text_size; }
    int heading1Size() const { return _heading_1_size; }
    int heading2Size() const { return _heading_2_size; }
    int cmdTextSize() const { return _cmd_text_size; }
    int subCmdTextSize() const { return _sub_cmd_text_size; }
    int normalTextSize() const { return _normal_text_size; }
    int nounTextSize() const { return _noun_text_size; }
    qreal pageItemWidth() const { return _page_item_width; }
    qreal pageItemHeight() const { return _page_item_height; }
    qreal themaItemWidth() const { return _thema_item_width; }
    qreal themaItemHeight() const { return _thema_item_height; }
    qreal cmdWidth() const { return _cmd_width; }
    qreal cmdHeight() const { return _cmd_height; }
    qreal msgBarHeight() const { return _msg_bar_height; }
    qreal panelFrameWidth() const { return _panel_frame_width; }
    qreal titleFrameHeight() const { return _title_frame_height; }

    void saveSettings();
    void loadSettings();

signals:
    void languageChanged();
    void soundLevelChanged();
    void wordMsgTimeChanged();
    void themaRemotePathChanged();
    void themaAutoUpdateChanged();
    //! Emitted when color palette instance changes.
    void colorPaletteChanged();

private slots:
    void disableThemaAutoUpdate();

private:
    void updateLangauge();
    //! Returns empty string. Hack used to language change in QML
    QString i18EmptyString() { return ""; }

    void clearTranslators();

    void setupDimesions();

private:
    //! Qml Context.
    QQmlContext& _qml_context;
    //! Selected language.
    Language_TP _current_language;
    //! Installed language translators.
    QList <QTranslator*> _installed_translators;
    //! Sound level.
    double _sound_level;
    //! Message time for info mode.
    int _word_message_time;
    //! Remote thema file's folder.
    QString _thema_remote_path;
    //! Flag for first run of application.
    bool _first_run;
    //! Auto update thema files.
    bool _thema_auto_update;
    //! Flag to check whether fortnightly thema update is done.
    QDateTime _thema_auto_update_date;
    //! Flag to update thema files at startup.
    bool _startup_thema_update;
    //! Color palate instance.
    QObject* _color_palette;
    bool _mobile_platforms;

    int _title_text_size;
    int _heading_1_size;
    int _heading_2_size;
    int _cmd_text_size;
    int _sub_cmd_text_size;
    int _normal_text_size;
    int _noun_text_size;
    qreal _page_item_width;
    qreal _page_item_height;
    qreal _thema_item_width;
    qreal _thema_item_height;
    qreal _cmd_width;
    qreal _cmd_height;
    qreal _msg_bar_height;
    qreal _panel_frame_width;
    qreal _title_frame_height;
};

#endif // SETTINGS_H
