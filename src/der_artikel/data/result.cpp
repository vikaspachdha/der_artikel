#include "result.h"

Result_C::Result_C():
    _score(0.0),
    _correct_word_count(0),
    _mistakes_count(0),
    _unplayed_count(0)
{
}

double Result_C::CorrectWordCount() const
{
    return _correct_word_count;
}

void Result_C::SetCorrectWordCount(double correct_word_count)
{
    _correct_word_count = correct_word_count;
}

double Result_C::Score() const
{
    return _score;
}

void Result_C::SetScore(double score)
{
    _score = score;
}
double Result_C::MistakesCount() const
{
    return _mistakes_count;
}

void Result_C::SetMistakesCount(double mistakes_count)
{
    _mistakes_count = mistakes_count;
}
double Result_C::UnplayedCount() const
{
    return _unplayed_count;
}

void Result_C::SetUnplayedCount(double unplayed_count)
{
    _unplayed_count = unplayed_count;
}

void Result_C::Clear()
{
    _score=0.0;
    _correct_word_count=0;
    _mistakes_count=0;
    _unplayed_count=0;
}



