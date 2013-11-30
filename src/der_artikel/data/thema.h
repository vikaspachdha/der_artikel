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
    Q_PROPERTY(bool selected READ Selected WRITE SetSelected NOTIFY selectionChanged)
    Q_PROPERTY(int experience READ ExperiencePoints NOTIFY experiencePointsChanged)

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
    void SetSelected(bool selected);

    const QUrl& GetIconUrl() const { return _icon_url; }

    int ExperiencePoints() const { return _experience_points; }

    QDateTime LastPlayed() const { return _last_played; }
    void SetLastPlayed(const QDateTime &LastPlayed);

    // Thema_I implementation
public:
    virtual unsigned int GetWordCount() const;
    virtual const Word_C* GetWord(unsigned int index) const;
    virtual void AddExperiencePoints(int points);
    virtual void DeductExperiencePoints(int points);


public:
    bool Read(const QDomElement& element);
    bool Write(QDomElement& element);
    void Save(QString file_path="");
    void ClearWords();


signals:
    void selectionChanged();
    void experiencePointsChanged();

private:
    bool Write(QIODevice* pDevice);

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


private:
    friend class ThemaBuilder_C;
};

#endif // THEMA_H
