#ifndef THEMA_H
#define THEMA_H
#include <QObject>
#include <QDomElement>
#include <QVector>
#include "word.h"

class Thema_C : public QObject
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

public:
    bool Read(const QDomElement& element);
    bool Write(QDomElement& element);
    void ClearWords();
    uint GetWordCount() const;
    uint GetCorrectArticleCount() const;

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
