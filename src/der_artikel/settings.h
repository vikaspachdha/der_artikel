#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QHash>

class QTranslator;

/**
 * @brief
 *
 */
class Settings_C : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Language_TP language READ Language WRITE SetLanguage NOTIFY LanguageChanged)
    Q_PROPERTY(QString i18n_empty_string READ GetEmptyString NOTIFY LanguageChanged)
    Q_PROPERTY(double sound_level READ soundLevel WRITE setSoundLevel NOTIFY soundLevelChanged)
    Q_PROPERTY(QString word_msg_time_str READ wordMsgTimeStr WRITE setWordMsgTimeStr NOTIFY wordMsgTimeChanged)
    Q_PROPERTY(int word_msg_time READ wordMsgTime WRITE setWordMsgTime NOTIFY wordMsgTimeChanged)
    Q_PROPERTY(int min_word_msg_time READ minWordMsgTime CONSTANT)
    Q_PROPERTY(int max_word_msg_time READ maxWordMsgTime CONSTANT)
    Q_ENUMS(Language_TP)

public:

    /**
     * @brief
     *
     */
    enum Language_TP {
        INVALID_LANGUAGE,
        ENGLISH,
        GERMAN,
        HINDI
    };

public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit Settings_C(QObject *parent = 0);

public:
    /**
     * @brief
     *
     * @return Language_TP
     */
    Language_TP Language() const { return _current_language; }
    /**
     * @brief
     *
     * @param language
     */
    void SetLanguage(Language_TP language);

    /**
     * @brief
     *
     * @return double
     */
    double soundLevel() const { return _sound_level; }
    /**
     * @brief
     *
     * @param sound_level
     */
    void setSoundLevel(double sound_level);

    /**
     * @brief
     *
     * @return QString
     */
    QString wordMsgTimeStr() const;
    /**
     * @brief
     *
     * @param new_time_str
     */
    void setWordMsgTimeStr(QString new_time_str);

    /**
     * @brief
     *
     * @return int
     */
    int wordMsgTime() const {return _word_message_time; }
    /**
     * @brief
     *
     * @param new_time
     */
    void setWordMsgTime(int new_time);

    /**
     * @brief
     *
     * @return int
     */
    int minWordMsgTime() const;
    /**
     * @brief
     *
     * @return int
     */
    int maxWordMsgTime() const;

signals:
    /**
     * @brief
     *
     */
    void LanguageChanged();
    /**
     * @brief
     *
     */
    void soundLevelChanged();
    /**
     * @brief
     *
     */
    void wordMsgTimeChanged();

private:
    /**
     * @brief
     *
     */
    void updateLangauge();
    /**
     * @brief
     *
     * @return QString
     */
    QString GetEmptyString() { return ""; }

private:
    Language_TP _current_language; /**< TODO */
    QList <QTranslator*> _installed_translators; /**< TODO */
    double _sound_level; /**< TODO */
    int _word_message_time; /**< TODO */
};

#endif // SETTINGS_H
