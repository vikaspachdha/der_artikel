#ifndef ARTICLE_H
#define ARTICLE_H

#include <QObject>

class Article_C : public QObject
{
    Q_OBJECT
    Q_ENUMS(Artikel)
    Q_DISABLE_COPY(Article_C)
public:
    enum Artikel
    {
        DER = 1,
        DIE,
        DAS,
        NA,
        INVALID
    };

private:
    explicit Article_C(QObject *parent = 0);

};

#endif // ARTICLE_H
