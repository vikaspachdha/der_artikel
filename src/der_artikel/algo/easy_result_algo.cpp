#include "easy_result_algo.h"
#include "data/word.h"
#include "data/thema.h"
#include "data/result.h"


/*!
 \brief

*/
EasyResultAlgo_C::EasyResultAlgo_C():ResultAlgo_I()
{
}

/*!
 \brief

 \param thema
 \param result
*/
void EasyResultAlgo_C::Calculate(Thema_I& thema, Result_C& result)
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
                incorrect_words<<word;
            }
        }

    }

    double score = (double)(correct_count)/count;

    result.updateResult(score,correct_count, unplayed_count, incorrect_words);

    Result_C::GRADE grade = result.grade();
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
    thema.AddExperiencePoints(exp_change);
    result.setExperienceChange(exp_change);
}

/*!
 \brief

 \param thema
 \return int
*/
int EasyResultAlgo_C::playTime(Thema_I &thema)
{
    return thema.wordCount()*4;
}
