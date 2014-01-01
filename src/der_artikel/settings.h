#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings_C : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Language_TP language READ Language WRITE SetLanguage NOTIFY LanguageChanged)
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

signals:
    void LanguageChanged();

private:
    Language_TP _current_language;
};

#endif // SETTINGS_H
