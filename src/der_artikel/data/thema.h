#ifndef THEMA_H
#define THEMA_H
#include <QObject>
#include <QDomElement>
#include <QHash>
#include "word.h"

class Thema_C
{
public:
    Thema_C();

public:
    bool Read(const QDomElement& element);

private:
    QString _text;
    QString _translation;
    QHash<QObject*, Word_C*> _words;
};

#endif // THEMA_H
