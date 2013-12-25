#ifndef THEMA_H
#define THEMA_H
#include <QObject>
#include <QDomElement>
#include <QDateTime>
#include <QVector>
#include <QUrl>
#include "word.h"
#include "thema_interface.h"

class QIODevice;


class Thema_C : public QObject, public Thema_I
{

    Q_OBJECT

    Q_PROPERTY(bool selected READ Selected NOTIFY selectionChanged)
    Q_PROPERTY(int experience READ ExperiencePoints NOTIFY experiencePointsChanged)
    Q_PROPERTY(QUrl icon_url READ GetIconUrl CONSTANT)
    Q_PROPERTY(QString name READ GetText CONSTANT)
    Q_PROPERTY(QString tr_name READ GetTrText CONSTANT)
    Q_PROPERTY(unsigned int word_count READ GetWordCount CONSTANT)
    Q_PROPERTY(QDateTime last_played_date READ LastPlayed CONSTANT)
    Q_PROPERTY(State_TP state READ state NOTIFY stateChanged)

    Q_ENUMS(State_TP)
    Q_ENUMS(SelectionType_TP)

public:
    enum State_TP {
        RUSTY,
        SILVER,
        GOLD,
        INERT
    };

    enum SelectionType_TP {
        SINGLE_SELECTION,
        MULTI_SELECTION
    };

public:
    Thema_C(QObject* parent = 0);
    ~Thema_C();

public:

    void SetText(QString text) { _text = text; }
    QString GetText() const { return _text; }

    void SetTrText(QString text) { _translation = text; }
    QString GetTrText() const { return _translation; }

    void SetFilePath(QString file_path);

    QVector<Word_C*> GetWords() const { return _words; }

    bool Selected() const { return _selected; }
    Q_INVOKABLE void setSelected(bool selected, SelectionType_TP type = SINGLE_SELECTION);

    const QUrl& GetIconUrl() const { return _icon_url; }

    int ExperiencePoints() const { return _experience_points; }

    QDateTime LastPlayed() const { return _last_played; }
    void SetLastPlayed(const QDateTime &LastPlayed);

    State_TP state() const { return _state; }

    // Thema_I implementation
public:
    virtual unsigned int GetWordCount() const;
    virtual const Word_C* GetWord(unsigned int index) const;
    virtual void AddExperiencePoints(int points);
    virtual void DeductExperiencePoints(int points);
    virtual void ClearUserInput();

public:
    bool Read(const QDomElement& element);
    bool Write(QDomElement& element);
    void Save(QString file_path="");
    void ClearWords();


signals:
    void selectionChanged(Thema_C::SelectionType_TP);
    void experiencePointsChanged();
    void stateChanged();

private:
    bool Write(QIODevice* pDevice);
    void UpdateThemaState();

private:
    QString _text;
    QString _translation;
    QString _file_path;
    QVector<Word_C*> _words;
    bool _defered_read;
    QDateTime _last_played;
    int _experience_points;
    bool _selected;
    QUrl _icon_url;
    State_TP _state;

private:
    friend class ThemaBuilder_C;
};

Q_DECLARE_METATYPE(Thema_C::SelectionType_TP)

#endif // THEMA_H
