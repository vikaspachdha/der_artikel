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

/**
 * @brief
 *
 */
class Result_C : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double score READ Score NOTIFY resultUpdated)
    Q_PROPERTY(unsigned int mistakes_count READ MistakesCount NOTIFY resultUpdated)
    Q_PROPERTY(unsigned int unplayed_count READ UnplayedCount NOTIFY resultUpdated)
    Q_PROPERTY(int experience_change READ ExperienceChange NOTIFY experienceChanged)
    Q_PROPERTY(unsigned int correct_word_count READ CorrectWordCount NOTIFY resultUpdated)
    Q_PROPERTY(QString score_string READ ScoreString NOTIFY resultUpdated)
    Q_PROPERTY(QString mistake_string READ MistakeString NOTIFY resultUpdated)
    Q_PROPERTY(QString grade_string READ GradeString NOTIFY resultUpdated)
    Q_PROPERTY(QString unplayed_string READ UnplayedString NOTIFY resultUpdated)
    Q_PROPERTY(QAbstractItemModel* incorrectWordsModel READ GetIncorrectWordModel CONSTANT)

public:

    /**
     * @brief
     *
     */
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
    /**
     * @brief
     *
     * @param parent
     */
    explicit Result_C(QObject* parent=0);

signals:
    /**
     * @brief
     *
     */
    void resultUpdated();
    /**
     * @brief
     *
     */
    void experienceChanged();

public:

    /**
     * @brief
     *
     * @return double
     */
    double Score() const;
    /**
     * @brief
     *
     * @return QString
     */
    QString ScoreString() const {return _score_string; }

    /**
     * @brief
     *
     * @return unsigned int
     */
    unsigned int MistakesCount() const;
    /**
     * @brief
     *
     * @return QString
     */
    QString MistakeString() const {return _mistake_string; }

    /**
     * @brief
     *
     * @return double
     */
    double UnplayedCount() const;

    /**
     * @brief
     *
     * @return int
     */
    int ExperienceChange() const { return _experience_change; }
    /**
     * @brief
     *
     * @param change
     */
    void setExperienceChange(int change);

    /**
     * @brief
     *
     * @return QString
     */
    QString GradeString() const {return _grade_string; }

    /**
     * @brief
     *
     * @return QString
     */
    QString UnplayedString() const {return _unplayed_string; }

    /**
     * @brief
     *
     * @return unsigned int
     */
    unsigned int CorrectWordCount() const;

    /**
     * @brief
     *
     * @return GRADE
     */
    GRADE Grade() const { return _grade; }

    /**
     * @brief
     *
     * @return QAbstractItemModel
     */
    QAbstractItemModel* GetIncorrectWordModel() { return _incorrect_words_model; }

public:
    /**
     * @brief
     *
     */
    void Clear();
    /**
     * @brief
     *
     * @param score
     * @param correct_word_count
     * @param unplayed_count
     * @param incorrect_words
     */
    void UpdateResult(double score, unsigned int correct_word_count, unsigned int unplayed_count, QList<const Word_C *> incorrect_words);
    /**
     * @brief
     *
     * @param element
     * @return bool
     */
    bool Read(const QDomElement& element);
    /**
     * @brief
     *
     * @param element
     * @return bool
     */
    bool Write(QDomElement& element);

private:
    /**
     * @brief
     *
     */
    void UpdateStringData();

private:
    double _score; /**< TODO */
    GRADE _grade; /**< TODO */
    unsigned int _correct_word_count; /**< TODO */
    unsigned int _mistakes_count; /**< TODO */
    unsigned int _unplayed_count; /**< TODO */
    int _experience_change; /**< TODO */
    QString _score_string; /**< TODO */
    QString _mistake_string; /**< TODO */
    QString _grade_string; /**< TODO */
    QString _unplayed_string; /**< TODO */
    QDateTime _result_date_time; /**< TODO */
    WordModel_C* _incorrect_words_model; /**< TODO */
};

#endif // RESULT_H
