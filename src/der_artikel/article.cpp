#include "article.h"

Article_C::Article_C(QObject *parent) :
    QObject(parent)
{
}

QString Article_C::ArtikelText(Article_C::Artikel artikel)
{
    QString text;
    switch(artikel)
    {
    case DER:
        text = "Der";
        break;

    case DIE:
        text = "Die";
        break;

    case DAS:
        text = "Das";
        break;

    default:
        text = "";
        break;

    }

    return text;
}
