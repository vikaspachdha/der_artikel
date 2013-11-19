#include "thema.h"
#include <QDebug>
#include <QPixmap>
#include <QFileInfo>
#include <QDir>

Thema_C::Thema_C(QObject *parent): QObject(parent),
    _text(""),
    _translation(""),
    _defered_read(false),
    _3rd_last_score(0.0),
    _2nd_last_score(0.0),
    _last_score(0.0),
    _played_count(0)
{
    _icon_url = QUrl("qrc:/res/resources/thema_generic.png");
}

Thema_C::~Thema_C()
{
    ClearWords();
}

void Thema_C::SetFilePath(QString file_path)
{
    _file_path = file_path;
    QFileInfo file_info(file_path);
    QString icon_file_path = file_info.absoluteDir().absolutePath() + QDir::separator() + file_info.baseName() + ".png";

    QFileInfo icon_file(icon_file_path);
    if(icon_file.exists()) {
        _icon_url =QUrl(icon_file_path);
    }
}

bool Thema_C::Read(const QDomElement &element)
{
    bool success = false;
    ClearWords();
    if(!element.isNull()) {
        _text = element.firstChildElement("ThemaText").text();
        success = !_text.isEmpty();

        _translation = element.firstChildElement("Translation").text();

        QDomElement words_root_node = element.firstChildElement("Words");

        QDomNode word_node = words_root_node.firstChild();

        while(!word_node.isNull()) {
            Word_C* word = new Word_C(this);
            if(!word->Read(word_node.toElement())) {
                delete word;
                qDebug()<<"Invalid Word in thema.";
            } else {
                _words.append(word);
            }
            word_node = word_node.nextSibling();
        }

    }


    return success;
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

            QDomElement dom_words_root = domDocument.createElement("Words");

            QVector<Word_C*>::Iterator iter =_words.begin();
            while(iter != _words.end()) {
                Word_C* word = *iter;
                if(word) {
                    word->Write(dom_words_root);
                }
                ++iter;
            }

            dom_thema.appendChild(dom_words_root);
            element.appendChild(dom_thema);

            success = true;
        }
    }

    return success;
}

void Thema_C::ClearWords()
{
    foreach(Word_C* word, _words) {
        delete word;
    }
    _words.clear();
}

void Thema_C::SetSelected(bool selected)
{
    _selected = selected;
}

unsigned int Thema_C::GetWordCount() const
{
    return (uint)_words.count();
}

const Word_C *Thema_C::GetWord(unsigned int index) const
{
    Word_C* word = 0;
    if(index < _words.count()) {
        word = _words.at(index);
    }
    return word;
}


