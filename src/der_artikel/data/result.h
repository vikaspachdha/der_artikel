#ifndef RESULT_H
#define RESULT_H
#include <QObject>
#include <QDateTime>

class QDomElement;

class Result_C : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double score READ Score CONSTANT)
    Q_PROPERTY(unsigned int mistakes_count READ MistakesCount CONSTANT)
    Q_PROPERTY(unsigned int unplayed_count READ UnplayedCount CONSTANT)
    Q_PROPERTY(unsigned int correct_word_count READ CorrectWordCount CONSTANT)
    Q_PROPERTY(QString score_string READ ScoreString CONSTANT)
    Q_PROPERTY(QString mistake_string READ MistakeString CONSTANT)
    Q_PROPERTY(QString grade_string READ GradeString CONSTANT)
    Q_PROPERTY(QString unplayed_string READ UnplayedString CONSTANT)

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

public:
    void Clear();
    void UpdateResult(double score, unsigned int correct_word_count, unsigned int mistakes_count, unsigned int unplayed_count);
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
};

#endif // RESULT_H
