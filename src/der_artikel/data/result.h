#ifndef RESULT_H
#define RESULT_H
#include <QObject>

class Result_C : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double score READ Score)
    Q_PROPERTY(unsigned int mistakes_count READ MistakesCount)
    Q_PROPERTY(unsigned int unplayed_count READ UnplayedCount)
    Q_PROPERTY(unsigned int correct_word_count READ CorrectWordCount)

public:
    Result_C(QObject* parent=0);

signals:
    void resultUpdated();

public:

    double Score() const;

    unsigned int MistakesCount() const;

    double UnplayedCount() const;

    unsigned int CorrectWordCount() const;

public:
    void Clear();
    void UpdateResult(double score, unsigned int correct_word_count, unsigned int mistakes_count, unsigned int unplayed_count);

private:
    double _score;
    unsigned int _correct_word_count;
    unsigned int _mistakes_count;
    unsigned int _unplayed_count;
};

#endif // RESULT_H
