#ifndef WORD_H
#define WORD_H
#include "common.h"
#include <QDomElement>
#include <QObject>

class Word_C : public QObject
{
    Q_OBJECT
public:
    Word_C(QObject* parent=0);

public:
    void SetUserArtikel(ARTIKEL::Artikel article) { _user_artikel = article; }
    ARTIKEL::Artikel GetUserArtikel() const { return _user_artikel; }

    ARTIKEL::Artikel GetArtikel() const { return _artikel; }

    QString GetWordText() const { return _text; }

public:
    bool Read(const QDomElement& element);
    bool Write(QDomElement& element);
    bool IsCorrect() const;

private:
    QString _text;
    ARTIKEL::Artikel _artikel;
    ARTIKEL::Artikel _user_artikel;

private:
    friend class ThemaBuilder_C;
};

#endif // WORD_H
