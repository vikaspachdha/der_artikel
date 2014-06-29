//******************************************************************************
/*! \file easy_result_algo.cpp. Implementation of \ref EasyResultAlgo_C
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

// Interface for this file
#include "easy_result_algo.h"

// Framework and lib includes
#include "data/word.h"
#include "data/thema.h"
#include "data/result.h"


//******************************************************************************
/*! \brief Constructor
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
EasyResultAlgo_C::EasyResultAlgo_C():ResultAlgo_I()
{
}

//******************************************************************************
/*! \brief Calculates the result after the game play.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] thema : Thema instance.
 *  \param[out] result : Resut instance.
 ******************************************************************************/
void EasyResultAlgo_C::calculate(Thema_I& thema, Result_C& result)
{
    unsigned int count = thema.wordCount();
    unsigned int correct_count = 0;
    QList<const Word_C*>incorrect_words;
    unsigned int unplayed_count = 0;

    for(unsigned int index = 0; index < count; ++index) {
        const Word_C* word = thema.word(index);
        if(word->userArtikel() == Article_C::INVALID || word->userArtikel() == Article_C::NA) {
            ++unplayed_count;
        } else {
            if(word->artikel() == word->userArtikel()) {
                ++correct_count;
            } else {
                incorrect_words<<word->copy();
            }
        }

    }

    double score = (double)(correct_count)/count;

    result.updateResult(score,correct_count, unplayed_count, incorrect_words);

    Result_C::GRADE_TP grade = result.grade();
    int exp_change = 0;
    if(grade >= Result_C::GRADE_AP) {
        exp_change = 50;
    } else if(grade >= Result_C::GRADE_A) {
        exp_change = 40;
    } else if (grade >= Result_C::GRADE_BP) {
        exp_change = 30;
    } else if (grade >= Result_C::GRADE_B) {
        exp_change = 20;
    } else if (grade >= Result_C::GRADE_C) {
        exp_change = 10;
    } else if(grade >= Result_C::GRADE_D) {
        exp_change = 5;
    }
    thema.addExperiencePoints(exp_change);
    result.setExperienceChange(exp_change);
}

//******************************************************************************
/*! \brief Returns time to play a thema.
 *
 *  \details Time is propotional to words count in the thema to be played.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] thema : Thema instance.
 *
 *  \return int : Time in msecs.
 ******************************************************************************/
int EasyResultAlgo_C::playTime(Thema_I &thema)
{
    return thema.wordCount()*4;
}
