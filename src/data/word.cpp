#include "word.h"

/*!
 \brief

 \param parent
*/
Word_C::Word_C(QObject* parent): QObject(parent),
_text(""),
_artikel(Article_C::INVALID),
_user_artikel(Article_C::INVALID)
{
}

void Word_C::SetUserArtikel(Article_C::Artikel article)
{
    if(_user_artikel != article) {
        _user_artikel = article;
        emit userArticleChanged();
    }
}

/*!
 \brief

 \param element
 \return bool
*/
bool Word_C::Read(const QDomElement &element)
{
    bool success = false;
    if(!element.isNull()) {
        _text = element.firstChildElement("WordText").text();
        success = !_text.isEmpty();
        _description = element.firstChildElement("Description").text();

        int article_value = element.firstChildElement("Artikel").text().toInt(&success);
        if(success) {
            switch(article_value) {
            case Article_C::DAS:
            case Article_C::DER:
            case Article_C::DIE:
            case Article_C::NA:
                _artikel = (Article_C::Artikel) article_value;
                break;
            default:
                success = false;
                break;
            }
        }
    }
    return success;
}

/*!
 \brief

 \param element
 \return bool
*/
bool Word_C::Write(QDomElement &element)
{
    bool success = false;

    if( !element.isNull()) {
        QDomDocument domDocument = element.ownerDocument();

        if(!domDocument.isNull() && !_text.isEmpty() && _artikel != Article_C::INVALID) {
            QDomElement dom_word = domDocument.createElement("Word");

            QDomElement dom_text = domDocument.createElement("WordText");
            QDomText text_word = domDocument.createTextNode(_text);
            dom_text.appendChild(text_word);
            dom_word.appendChild(dom_text);

            QDomElement dom_description = domDocument.createElement("Description");
            QDomText text_description = domDocument.createTextNode(_description);
            dom_description.appendChild(text_description);
            dom_word.appendChild(dom_description);

            QDomElement dom_artikel = domDocument.createElement("Artikel");
            QDomText artikel_code = domDocument.createTextNode(QString::number(_artikel));
            dom_artikel.appendChild(artikel_code);
            dom_word.appendChild(dom_artikel);

            element.appendChild(dom_word);
            success = true;
        }
    }

    return success;
}

/*!
 \brief

 \return bool
*/
bool Word_C::IsCorrect() const
{
    bool correct = false;

    if( (_artikel != Article_C::INVALID)
            && (_user_artikel != Article_C::INVALID)
            && (_artikel == _user_artikel) ) {
        correct = true;
    }

    return correct;
}
