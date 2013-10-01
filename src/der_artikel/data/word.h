#ifndef WORD_H
#define WORD_H
#include "common.h"
#include <QDomElement>

class Word_C
{
public:
    Word_C();
public:
    ARTIKEL::Artikel GetUserArtikel() const { return _user_artikel; }
    ARTIKEL::Artikel GetArtikel() const { return _artikel; }

public:
    bool Read(const QDomElement& element);
    bool Write(QDomElement& element);
    bool IsCorrect() const;

private:
    QString _text;
    ARTIKEL::Artikel _artikel;
    ARTIKEL::Artikel _user_artikel;
};

#endif // WORD_H
