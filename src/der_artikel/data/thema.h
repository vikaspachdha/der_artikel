#ifndef THEMA_H
#define THEMA_H
#include <QObject>
#include <QDomElement>
#include <QVector>
#include "word.h"
#include "thema_interface.h"

class Thema_C : public QObject, public Thema_I
{

    Q_OBJECT
public:
    Thema_C(QObject* parent = 0);
    ~Thema_C();

public:

    void SetText(QString text) { _text = text; }
    QString GetText() const { return _text; }

    void SetTrText(QString text) { _translation = text; }
    QString GetTrText() const { return _translation; }

    void SetFilePath(QString file_path) { _file_path = file_path; }

    QVector<Word_C*> GetWords() const { return _words; }

    // Thema_I implementation
public:
    virtual unsigned int GetWordCount() const;
    virtual const Word_C* GetWord(unsigned int index) const;

public:
    bool Read(const QDomElement& element);
    bool Write(QDomElement& element);
    void ClearWords();

private:
    QString _text;
    QString _translation;
    QString _file_path;
    QVector<Word_C*> _words;
    bool _defered_read;
    double _3rd_last_score;
    double _2nd_last_score;
    double _last_score;
    double _played_count;


private:
    friend class ThemaBuilder_C;
};

#endif // THEMA_H
