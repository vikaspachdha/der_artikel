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

public:
    void Clear();
    void UpdateResult(double score, unsigned int correct_word_count, unsigned int mistakes_count, unsigned int unplayed_count);
    bool Read(const QDomElement& element);
    bool Write(QDomElement& element);

private:
    void UpdateStringData();

private:
    double _score;
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
