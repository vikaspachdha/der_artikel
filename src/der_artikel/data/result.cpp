#include "result.h"
#include <QLocale>
#include <QDomElement>
#include "data/word.h"
#include "word_model.h"

Result_C::Result_C(QObject *parent):
    QObject(parent),
    _score(0.0),
    _correct_word_count(0),
    _mistakes_count(0),
    _unplayed_count(0),
    _score_string(tr("No game data.")),
    _mistake_string(""),
    _grade_string(tr("Result")),
    _unplayed_string("")
{
    _incorrect_words_model = new WordModel_C(this);
}

unsigned int Result_C::CorrectWordCount() const
{
    return _correct_word_count;
}

double Result_C::Score() const
{
    return _score;
}

unsigned int Result_C::MistakesCount() const
{
    return _mistakes_count;
}

double Result_C::UnplayedCount() const
{
    return _unplayed_count;
}

void Result_C::Clear()
{
    _score=0.0;
    _correct_word_count=0;
    _mistakes_count=0;
    _unplayed_count=0;

    _score_string = tr("No game data.");
    _mistake_string = "";
    _grade_string = tr("Result");
    _unplayed_string="";
}

void Result_C::UpdateResult(double score, unsigned int correct_word_count, unsigned int unplayed_count, QList<const Word_C*>incorrect_words)
{
    if(score <0.0) {
        score = 0.0;
    }
    _score = score;
    _correct_word_count= correct_word_count;
    _mistakes_count= incorrect_words.count();
    _unplayed_count= unplayed_count;
    _incorrect_words_model->UpdateWords(incorrect_words);

    double percentage_score = _score *100.0;

    if(percentage_score > 94.99) {
        _grade = GRADE_AP;
    } else if(percentage_score > 89.99) {
        _grade = GRADE_A;
    } else if(percentage_score > 79.99) {
        _grade = GRADE_BP;
    } else if(percentage_score > 69.99) {
        _grade = GRADE_B;
    } else if(percentage_score > 59.99) {
        _grade = GRADE_C;
    } else if(percentage_score > 49.99) {
        _grade = GRADE_D;
    } else  {
        _grade = GRADE_E;
    }

    UpdateStringData();
    emit resultUpdated();
}

bool Result_C::Read(const QDomElement &element)
{
    bool success = false;

    if(!element.isNull()) {
        bool ok = false;
        QDomElement dom_date_time = element.firstChildElement("DateTime");
        if(!dom_date_time.isNull()) {
            qint64 msecs = dom_date_time.text().toLongLong(&ok);
            if(ok) {
                _result_date_time = QDateTime::fromMSecsSinceEpoch(msecs);
                success = true;
            } else {
                success = false;
            }
        }

        if(success) {
            QDomElement dom_score = element.firstChildElement("Score");
            if(!dom_score.isNull()) {
                ok= false;
                double score = dom_score.text().toDouble(&ok);
                if(ok) {
                    _score = score;
                    success = true;
                } else {
                    success = false;
                }
            }
        }

        if(success) {
            QDomElement dom_correct_count = element.firstChildElement("CorrectCount");
            if(!dom_correct_count.isNull()) {
                ok= false;
                unsigned int count = dom_correct_count.text().toUInt(&ok);
                if(ok) {
                    _correct_word_count = count;
                    success = true;
                } else {
                    success = false;
                }
            }
        }

        if(success) {
            QDomElement dom_mistakes_count = element.firstChildElement("MistakesCount");
            if(!dom_mistakes_count.isNull()) {
                ok= false;
                unsigned int count = dom_mistakes_count.text().toUInt(&ok);
                if(ok) {
                    _mistakes_count = count;
                    success = true;
                } else {
                    success = false;
                }
            }
        }

        if(success) {
            QDomElement dom_unplayed_count = element.firstChildElement("UnplayedCount");
            if(!dom_unplayed_count.isNull()) {
                ok= false;
                unsigned int count = dom_unplayed_count.text().toUInt(&ok);
                if(ok) {
                    _unplayed_count = count;
                    success = true;
                } else {
                    success = false;
                }
            }
        }

        if(success) {
            UpdateStringData();
        }

    }
    return success;
}

bool Result_C::Write(QDomElement &element)
{
    bool success = false;

    if( !element.isNull()) {
        QDomDocument domDocument = element.ownerDocument();

        if(!domDocument.isNull()) {
            QDomElement dom_result = domDocument.createElement("Result");

            QDomElement dom_date_time = domDocument.createElement("DateTime");
            QDomText text_date_time = domDocument.createTextNode(QString::number(_result_date_time.toMSecsSinceEpoch()));
            dom_date_time.appendChild(text_date_time);
            dom_result.appendChild(dom_date_time);

            QDomElement dom_score = domDocument.createElement("Score");
            QDomText text_score = domDocument.createTextNode(QString::number(_score,'f',2));
            dom_score.appendChild(text_score);
            dom_result.appendChild(dom_score);

            QDomElement dom_correct_count = domDocument.createElement("CorrectCount");
            QDomText text_correct_count = domDocument.createTextNode(QString::number(_correct_word_count));
            dom_correct_count.appendChild(text_correct_count);
            dom_result.appendChild(dom_correct_count);

            QDomElement dom_mistakes_count = domDocument.createElement("MistakesCount");
            QDomText text_mistakes_count = domDocument.createTextNode(QString::number(_mistakes_count));
            dom_mistakes_count.appendChild(text_mistakes_count);
            dom_result.appendChild(dom_mistakes_count);

            QDomElement dom_unplayed_count = domDocument.createElement("UnplayedCount");
            QDomText text_unplayed_count = domDocument.createTextNode(QString::number(_unplayed_count));
            dom_unplayed_count.appendChild(text_unplayed_count);
            dom_result.appendChild(dom_unplayed_count);

            element.appendChild(dom_result);

            success = true;
        }
    }

    return success;
}

void Result_C::UpdateStringData()
{
    QLocale locale;
    double score = _score*100;
    _score_string = tr("Score : %1 %").arg(locale.toString(score,'f',2));
    _mistake_string = tr("Mistakes : %1").arg(_mistakes_count);
    _unplayed_string = tr("Unplayed : %1").arg(_unplayed_count);

    if(_grade >= GRADE_AP) {
        _grade_string = tr("Execelent");
    } else if(_grade >= GRADE_A) {
        _grade_string = tr("Very good");
    } else if (_grade >= GRADE_BP) {
        _grade_string = tr("Good");
    } else if (_grade >= GRADE_C) {
        _grade_string = tr("Satisfactory");
    } else if(_grade >= GRADE_D){
        _grade_string = tr("Sufficient");
    } else {
        _grade_string = tr("Failed");
    }

    _grade_string.prepend(tr("Result : "));
}



