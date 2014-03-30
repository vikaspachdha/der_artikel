#include "article.h"
#include "log_defines.h"
/*!
 \brief

 \param parent
*/
Article_C::Article_C(QObject *parent) :
    QObject(parent)
{
}

/*!
 \brief

 \param artikel
 \return QString
*/
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
        LOG_DEBUG("ArtikelText::INVALID");
        break;

    }

    return text;
}
