#include "thema.h"
#include <QDebug>
#include <QPixmap>
#include <QFileInfo>
#include <QDir>

#include "version.h"

Thema_C::Thema_C(QObject *parent): QObject(parent),
    _text(""),
    _translation(""),
    _defered_read(false),
    _last_played(QDateTime::currentDateTime()),
    _experience_points(0)
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

        bool ok = false;
        QDomElement dom_date_time = element.firstChildElement("LastPlayed");
        if(!dom_date_time.isNull()) {
            qint64 msecs = dom_date_time.text().toLongLong(&ok);
            if(ok) {
                _last_played = QDateTime::fromMSecsSinceEpoch(msecs);
                success = true;
            } else {
                success = false;
            }
        }

        if(success) {
            QDomElement dom_experience = element.firstChildElement("ExperiencePoints");
            if(!dom_experience.isNull()) {
                ok= false;
                int experience = dom_experience.text().toInt(&ok);
                if(ok) {
                    _experience_points = experience;
                    success = true;
                } else {
                    success = false;
                }
            }
        }

        if(success) {
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

            QDomElement dom_experience = domDocument.createElement("ExperiencePoints");
            QDomText text_experience = domDocument.createTextNode(QString::number(_experience_points));
            dom_experience.appendChild(text_experience);
            dom_thema.appendChild(dom_experience);

            QDomElement dom_last_played = domDocument.createElement("LastPlayed");
            QDomText text_last_played = domDocument.createTextNode(QString::number(_last_played.toMSecsSinceEpoch()));
            dom_last_played.appendChild(text_last_played);
            dom_thema.appendChild(dom_last_played);

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

void Thema_C::Save(QString file_path)
{
    QString save_file = file_path.isEmpty() ? _file_path : file_path;

    if(!save_file.isEmpty()) {
        QFile file(save_file);
        if (file.open(QFile::WriteOnly | QFile::Text)) {
            if(Write(&file)) {
                _file_path = save_file;
            }
        } else {
            qDebug()<<QString("cannot write file %1:\n%2.") .arg(save_file) .arg(file.errorString());
        }
    }
}

void Thema_C::ClearWords()
{
    foreach(Word_C* word, _words) {
        delete word;
    }
    _words.clear();
}

bool Thema_C::Write(QIODevice* pDevice)
{
    QDomDocument domDocument("DerArtikel");

    QTextStream out(pDevice);
    QDomElement root = domDocument.createElement("Root");
    root.setAttribute("Version", QString::number(APP_VERSION));

    Write(root);

    domDocument.appendChild(root);
    domDocument.save(out, 4);

    return true;
}

void Thema_C::AddExperiencePoints(int points)
{
    _experience_points += points;
    if(_experience_points < 0) {
        _experience_points = 0;
    }

    if(points !=0) {
        emit experiencePointsChanged();
    }
}

void Thema_C::DeductExperiencePoints(int points)
{
    AddExperiencePoints(-points);
}

void Thema_C::SetLastPlayed(const QDateTime &last_played)
{
    _last_played = last_played;
}

void Thema_C::SetSelected(bool selected)
{
    if(_selected != selected) {
        _selected = selected;
        emit selectionChanged();
    }
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


