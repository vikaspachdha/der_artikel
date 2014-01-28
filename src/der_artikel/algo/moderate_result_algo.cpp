#include "moderate_result_algo.h"
#include "data/word.h"
#include "data/thema.h"
#include "data/result.h"


/*!
 \brief

*/
ModerateResultAlgo_C::ModerateResultAlgo_C():ResultAlgo_I()
{
}

/*!
 \brief

 \param thema
 \param result
*/
void ModerateResultAlgo_C::Calculate(Thema_I& thema, Result_C& result)
{
    unsigned int count = thema.GetWordCount();
    unsigned int correct_count = 0;
    QList<const Word_C*>incorrect_words;
    unsigned int unplayed_count = 0;

    for(unsigned int index = 0; index < count; ++index) {
        const Word_C* word = thema.GetWord(index);
        if(word->GetUserArtikel() == Article_C::INVALID || word->GetUserArtikel() == Article_C::NA) {
            ++unplayed_count;
        } else {
            if(word->GetArtikel() == word->GetUserArtikel()) {
                ++correct_count;
            } else {
                incorrect_words<<word;
            }
        }

    }

    double score = (double)(correct_count - (incorrect_words.count()/2.0))/count;

    result.UpdateResult(score,correct_count, unplayed_count, incorrect_words);

    Result_C::GRADE grade = result.Grade();
    int exp_change = 0;
    if(grade >= Result_C::GRADE_AP) {
        exp_change = 80;
    } else if(grade >= Result_C::GRADE_A) {
        exp_change = 60;
    } else if (grade >= Result_C::GRADE_BP) {
        exp_change = 50;
    } else if (grade >= Result_C::GRADE_B) {
        exp_change = 40;
    } else if (grade >= Result_C::GRADE_C) {
        exp_change = 30;
    } else if(grade >= Result_C::GRADE_D){
        exp_change = 20;
    } else {
        exp_change = -10;
    }
    thema.AddExperiencePoints(exp_change);
    result.setExperienceChange(exp_change);
}

/*!
 \brief

 \param thema
 \return int
*/
int ModerateResultAlgo_C::playTime(Thema_I &thema)
{
    return thema.GetWordCount() * 3;
}

