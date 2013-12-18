#ifndef RESULT_H
#define RESULT_H
#include <QObject>
#include <QDateTime>
#include <QList>
#include <QVariantList>
#include "data/word.h"
#include "word_model.h"

class QDomElement;
class Word_C;

class Result_C : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double score READ Score NOTIFY resultUpdated)
    Q_PROPERTY(unsigned int mistakes_count READ MistakesCount NOTIFY resultUpdated)
    Q_PROPERTY(unsigned int unplayed_count READ UnplayedCount NOTIFY resultUpdated)
    Q_PROPERTY(unsigned int correct_word_count READ CorrectWordCount NOTIFY resultUpdated)
    Q_PROPERTY(QString score_string READ ScoreString NOTIFY resultUpdated)
    Q_PROPERTY(QString mistake_string READ MistakeString NOTIFY resultUpdated)
    Q_PROPERTY(QString grade_string READ GradeString NOTIFY resultUpdated)
    Q_PROPERTY(QString unplayed_string READ UnplayedString NOTIFY resultUpdated)
    Q_PROPERTY(QAbstractItemModel* incorrectWordsModel READ GetIncorrectWordModel CONSTANT)

public:

    enum GRADE {
        GRADE_E=1,  // < 50
        GRADE_D,    // 50 - 60
        GRADE_C,    // 60 - 70
        GRADE_B,    // 70 - 80
        GRADE_BP,   // 80 - 90
        GRADE_A,    // 90 - 95
        GRADE_AP    // 95+
    };

public:
    Result_C(QObject* parent=0);

signals:
    void resultUpdated();

public:

    double Score() const;
    QString ScoreString() const {return _score_string; }

    unsigned int MistakesCount() const;
    QString MistakeString() const {return _mistake_string; }

    double UnplayedCount() const;

    QString GradeString() const {return _grade_string; }

    QString UnplayedString() const {return _unplayed_string; }

    unsigned int CorrectWordCount() const;

    GRADE Grade() const { return _grade; }

    QAbstractItemModel* GetIncorrectWordModel() { return _incorrect_words_model; }

public:
    void Clear();
    void UpdateResult(double score, unsigned int correct_word_count, unsigned int unplayed_count, QList<const Word_C *> incorrect_words);
    bool Read(const QDomElement& element);
    bool Write(QDomElement& element);

private:
    void UpdateStringData();

private:
    double _score;
    GRADE _grade;
    unsigned int _correct_word_count;
    unsigned int _mistakes_count;
    unsigned int _unplayed_count;
    QString _score_string;
    QString _mistake_string;
    QString _grade_string;
    QString _unplayed_string;
    QDateTime _result_date_time;
    WordModel_C* _incorrect_words_model;
};

#endif // RESULT_H
