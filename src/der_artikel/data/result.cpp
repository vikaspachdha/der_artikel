#include "result.h"
#include <QLocale>
#include <QDomElement>

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

void Result_C::UpdateResult(double score, unsigned int correct_word_count, unsigned int mistakes_count, unsigned int unplayed_count)
{
    QLocale locale;

    if(score <0.0) {
        score = 0.0;
    }
    _score = score;
    score = score*100;
    _correct_word_count= correct_word_count;
    _mistakes_count= mistakes_count;
    _unplayed_count= unplayed_count;

    _score_string = tr("You Scored %1 %").arg(locale.toString(score,'f',2));
    _mistake_string = tr("%1 articles are incorrect").arg(_mistakes_count);
    _unplayed_string = tr("%1 words are unplayed").arg(_unplayed_count);

    if(score > 89.99) {
        _grade_string = tr("Very good");
    } else if (score > 79.99) {
        _grade_string = tr("Good");
    } else if (score > 64.99) {
        _grade_string = tr("Satisfactory");
    } else if(score > 49.99){
        _grade_string = tr("Sufficient");
    } else {
        _grade_string = tr("Failed");
    }

    _grade_string.prepend(tr("Result : "));
    emit resultUpdated();
}

bool Result_C::Read(const QDomElement &element)
{
    bool success = false;
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



