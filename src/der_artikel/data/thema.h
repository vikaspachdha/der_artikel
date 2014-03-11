#ifndef THEMA_H
#define THEMA_H
#include <QObject>
#include <QDomElement>
#include <QDateTime>
#include <QPixmap>
#include <QList>
#include <QUrl>
#include "word.h"
#include "thema_interface.h"

class QIODevice;


class Thema_C : public QObject, public Thema_I
{

    Q_OBJECT

    Q_PROPERTY(bool selected READ Selected NOTIFY selectionChanged)
    Q_PROPERTY(int experience READ ExperiencePoints NOTIFY experiencePointsChanged)
    Q_PROPERTY(QString name READ GetText CONSTANT)
    Q_PROPERTY(QString tr_name READ GetTrText CONSTANT)
    Q_PROPERTY(unsigned int word_count READ GetWordCount CONSTANT)
    Q_PROPERTY(QDateTime last_played_date READ lastPlayed CONSTANT)
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

    QString GetText() const { return _text; }

    QString GetTrText() const { return _translation; }

    QString Author() const { return _author; }

    QString filePath() const { return _file_path; }

    void SetFilePath(QString file_path);

    QList<Word_C*> GetWords() const { return _words; }

    bool Selected() const { return _selected; }
    Q_INVOKABLE void setSelected(bool selected, SelectionType_TP type = SINGLE_SELECTION);

    const QPixmap& GetIcon() const { return _icon; }

    int ExperiencePoints() const { return _experience_points; }

    QDateTime lastPlayed() const { return _last_played; }
    void setLastPlayed(const QDateTime &Last_played);

    QDateTime LastUpdated() const { return _last_updated; }
    void setLastUpdated(const QDateTime &last_updated);

    State_TP state() const { return _state; }

    // Thema_I implementation
public:
    virtual unsigned int GetWordCount() const;
    virtual const Word_C* GetWord(int index) const;
    virtual void AddExperiencePoints(int points);
    virtual void DeductExperiencePoints(int points);
    virtual void ClearUserInput();

public:
    bool Read(QString thema_file_path, bool defered = true);
    bool Write(QDomElement& element);
    void Save(QString file_path="");
    void ClearWords();

signals:
    void selectionChanged(Thema_C::SelectionType_TP);
    void experiencePointsChanged();
    void stateChanged();

private:
    bool Read(const QDomElement& element, bool defered=true);
    bool Write(QIODevice* pDevice);
    void UpdateThemaState();
    QByteArray IconData() const;
    void UpdateIcon(QByteArray data);
    void ResetThema();

private:
    QString _text;
    QString _translation;
    QString _author;
    QString _file_path;
    QList<Word_C*> _words;
    QDateTime _last_played;
    QDateTime _last_updated;
    int _experience_points;
    bool _selected;
    QPixmap _icon;
    State_TP _state;

private:
    friend class ThemaBuilder_C;
};

Q_DECLARE_METATYPE(Thema_C::SelectionType_TP)

#endif // THEMA_H
