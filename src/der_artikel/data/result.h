#ifndef RESULT_H
#define RESULT_H

class Result_C
{
public:
    Result_C();

public:

    double Score() const;
    void SetScore(double score);

    double MistakesCount() const;
    void SetMistakesCount(double mistakes_count);

    double UnplayedCount() const;
    void SetUnplayedCount(double unplayed_count);

    double CorrectWordCount() const;
    void SetCorrectWordCount(double correct_word_count);

public:
    void Clear();
private:
    double _score;
    double _correct_word_count;
    double _mistakes_count;
    double _unplayed_count;
};

#endif // RESULT_H
