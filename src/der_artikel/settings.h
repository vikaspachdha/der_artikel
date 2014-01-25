#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QHash>

class QTranslator;

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

    enum Language_TP {
        INVALID_LANGUAGE,
        ENGLISH,
        GERMAN,
        HINDI
    };

public:
    explicit Settings_C(QObject *parent = 0);

public:
    Language_TP Language() const { return _current_language; }
    void SetLanguage(Language_TP language);

    double soundLevel() const { return _sound_level; }
    void setSoundLevel(double sound_level);

    QString wordMsgTimeStr() const;
    void setWordMsgTimeStr(QString new_time_str);

    int wordMsgTime() const {return _word_message_time; }
    void setWordMsgTime(int new_time);

    int minWordMsgTime() const;
    int maxWordMsgTime() const;

signals:
    void LanguageChanged();
    void soundLevelChanged();
    void wordMsgTimeChanged();

private:
    void updateLangauge();
    QString GetEmptyString() { return ""; }

private:
    Language_TP _current_language;
    QList <QTranslator*> _installed_translators;
    double _sound_level;
    int _word_message_time;
};

#endif // SETTINGS_H
