//******************************************************************************
/*! \file result.h Declaration of \ref Result_C
 *
 *  \author Vikas Pachdha
 *
 *  \copyright Copyright (C) 2014 Vikas Pachdha, Mohita Gandotra.
 * Contact: http://www.vikaspachdha.com
 *
 * This file is part of the application der_artikel.
 *
 *  \copyright GNU Lesser General Public License Usage
 * This file may be used under the terms of the GNU Lesser
 * General Public License version 2.1 as published by the Free Software
 * Foundation and appearing in the file LICENSE.LGPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU Lesser General Public License version 2.1 requirements
 * will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 *
 *  \copyright GNU General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 *
 ******************************************************************************/
#ifndef RESULT_H
#define RESULT_H
#include <QObject>
#include <QDateTime>
#include <QList>
#include <QVariantList>
#include "word.h"
#include "word_model.h"

class QDomElement;
class Word_C;

//******************************************************************************
/*! \brief Defines a result of a play session.
 *
 *  \details A result have parameters to define outcome of a game play but does
 *  not calculates it.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
class Result_C : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double score READ score NOTIFY resultUpdated)
    Q_PROPERTY(unsigned int mistakes_count READ mistakesCount NOTIFY resultUpdated)
    Q_PROPERTY(unsigned int unplayed_count READ unplayedCount NOTIFY resultUpdated)
    Q_PROPERTY(int experience_change READ experienceChange NOTIFY experienceChanged)
    Q_PROPERTY(unsigned int correct_word_count READ correctWordCount NOTIFY resultUpdated)
    Q_PROPERTY(QString score_string READ scoreString NOTIFY resultUpdated)
    Q_PROPERTY(QString mistake_string READ mistakeString NOTIFY resultUpdated)
    Q_PROPERTY(QString grade_string READ gradeString NOTIFY resultUpdated)
    Q_PROPERTY(QString unplayed_string READ unplayedString NOTIFY resultUpdated)
    Q_PROPERTY(QAbstractItemModel* incorrectWordsModel READ GetIncorrectWordModel CONSTANT)

public:
    //******************************************************************************
    /*! \brief Defines Grade of a result.
     *
     *  \details <ul>
     *              <li>GRADE E if score % < 50</li>
     *              <li>GRADE D if score % between 50 - 60</li>
     *              <li>GRADE C if score % between 60 - 70</li>
     *              <li>GRADE B if score % between 70 - 80</li>
     *              <li>GRADE B+ if score % between 80 - 90</li>
     *              <li>GRADE A if score % between 90 - 95</li>
     *              <li>GRADE A+ if score % > 95</li>
     *           </ul>
     *
     *  \author Vikas Pachdha
     ******************************************************************************/
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
    explicit Result_C(QObject* parent=0);

signals:
    void resultUpdated();
    void experienceChanged();

public:

    double score() const;
    //! Returns score string for display purpose.
    QString scoreString() const {return _score_string; }

    unsigned int mistakesCount() const;
    //! Returns unplayed words string for display purpose.
    QString mistakeString() const {return _mistake_string; }

    unsigned int unplayedCount() const;

    //! Returns experience change string for display purpose.
    int experienceChange() const { return _experience_change; }
    void setExperienceChange(int change);

    //! Returns grade achieved as string for display purpose..
    QString gradeString() const {return _grade_string; }

    //! Returns unplayed words string for display purpose.
    QString unplayedString() const {return _unplayed_string; }

    unsigned int correctWordCount() const;

    //! Returns grade achieved.
    GRADE grade() const { return _grade; }

    //! Returns incorrect word model.
    QAbstractItemModel* GetIncorrectWordModel() { return _incorrect_words_model; }

public:
    void clear();
    void updateResult(double score, unsigned int correct_word_count, unsigned int unplayed_count, QList<const Word_C *> incorrect_words);
    bool read(const QDomElement& element);
    bool write(QDomElement& element);

private:
    void updateStringData();

private:
    double _score;
    GRADE _grade;
    unsigned int _correct_word_count;
    unsigned int _mistakes_count;
    unsigned int _unplayed_count;
    int _experience_change;
    QString _score_string;
    QString _mistake_string;
    QString _grade_string;
    QString _unplayed_string;
    QDateTime _result_date_time;
    WordModel_C* _incorrect_words_model;
};

#endif // RESULT_H
