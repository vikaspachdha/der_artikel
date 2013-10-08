#include "thema.h"

Thema_C::Thema_C():
    _text(""),
    _translation("")
{
}

Thema_C::~Thema_C()
{
    foreach(Word_C* word, _words) {
        delete word;
    }
    _words.clear();
}

bool Thema_C::Read(const QDomElement &element)
{
    return true;
}

bool Thema_C::Write(QDomElement &element)
{
    bool success = false;

    if( !element.isNull()) {
        QDomDocument domDocument = element.ownerDocument();

        if(!domDocument.isNull() && !_text.isEmpty() && !_translation.isEmpty()) {
            QDomElement dom_thema = domDocument.createElement("Thema");

            QDomElement dom_text = domDocument.createElement("ThemaText");
            QDomText text_thema = domDocument.createTextNode(_text);
            dom_text.appendChild(text_thema);
            dom_thema.appendChild(dom_text);

            QDomElement dom_translation = domDocument.createElement("Translation");
            QDomText translation_thema = domDocument.createTextNode(_translation);
            dom_translation.appendChild(translation_thema);
            dom_thema.appendChild(dom_translation);

            QVector<Word_C*>::Iterator iter =_words.begin();
            while(iter != _words.end()) {
                Word_C* word = *iter;
                if(word) {
                    word->Write(dom_thema);
                }
                ++iter;
            }

            element.appendChild(dom_thema);
            success = true;
        }
    }

    return success;
}

