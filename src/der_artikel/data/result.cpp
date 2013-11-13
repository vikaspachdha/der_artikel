#include "result.h"

Result_C::Result_C(QObject *parent):
    QObject(parent),
    _score(0.0),
    _correct_word_count(0),
    _mistakes_count(0),
    _unplayed_count(0)
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
}

void Result_C::UpdateResult(double score, unsigned int correct_word_count, unsigned int mistakes_count, unsigned int unplayed_count)
{
    _score= score;
    _correct_word_count= correct_word_count;
    _mistakes_count= mistakes_count;
    _unplayed_count= unplayed_count;

    emit resultUpdated();
}



