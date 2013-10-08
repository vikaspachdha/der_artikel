#ifndef THEMA_H
#define THEMA_H
#include <QObject>
#include <QDomElement>
#include <QVector>
#include "word.h"

class Thema_C
{
public:
    Thema_C();
    ~Thema_C();

public:

    void SetText(QString text) { _text = text; }
    void SetTrText(QString text) { _translation = text; }

public:
    bool Read(const QDomElement& element);
    bool Write(QDomElement& element);

private:
    QString _text;
    QString _translation;
    QVector<Word_C*> _words;

private:
    friend class ThemaBuilder_C;
};

#endif // THEMA_H
