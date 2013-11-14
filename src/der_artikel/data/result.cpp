#include "result.h"

#include <QtQmlDepends>

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



