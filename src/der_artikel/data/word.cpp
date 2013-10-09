#include "word.h"

Word_C::Word_C(QObject* parent): QObject(parent),
_text(""),
_artikel(ARTIKEL::INVALID),
_user_artikel(ARTIKEL::INVALID)
{
}

bool Word_C::Read(const QDomElement &element)
{
    bool success = false;
    if(!element.isNull()) {
        _text = element.firstChildElement("WordText").text();
        success = !_text.isEmpty();

        int article_value = element.firstChildElement("Artikel").text().toInt(&success);
        if(success) {
            switch(article_value) {
            case ARTIKEL::DAS:
            case ARTIKEL::DER:
            case ARTIKEL::DIE:
            case ARTIKEL::NA:
                _artikel = (ARTIKEL::Artikel) article_value;
                break;
            default:
                success = false;
                break;
            }
        }
    }
    return success;
}

bool Word_C::Write(QDomElement &element)
{
    bool success = false;

    if( !element.isNull()) {
        QDomDocument domDocument = element.ownerDocument();

        if(!domDocument.isNull() && !_text.isEmpty() && _artikel != ARTIKEL::INVALID) {
            QDomElement dom_word = domDocument.createElement("Word");

            QDomElement dom_text = domDocument.createElement("WordText");
            QDomText text_word = domDocument.createTextNode(_text);
            dom_text.appendChild(text_word);
            dom_word.appendChild(dom_text);

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

bool Word_C::IsCorrect() const
{
    bool correct = false;

    if( (_artikel != ARTIKEL::INVALID)
            && (_user_artikel != ARTIKEL::INVALID)
            && (_artikel == _user_artikel) ) {
        correct = true;
    }

    return correct;
}
