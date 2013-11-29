#include "moderate_result_algo.h"
#include "data/word.h"
#include "data/thema.h"
#include "data/result.h"


ModerateResultAlgo_C::ModerateResultAlgo_C():ResultAlgo_I()
{
}

void ModerateResultAlgo_C::Calculate(Thema_I& thema, Result_C& result)
{
    unsigned int count = thema.GetWordCount();
    unsigned int correct_count = 0;
    unsigned int incorrect_count = 0;
    unsigned int unplayed_count = 0;

    for(unsigned int index = 0; index < count; ++index) {
        const Word_C* word = thema.GetWord(index);
        if(word->GetUserArtikel() == Article_C::INVALID || word->GetUserArtikel() == Article_C::NA) {
            ++unplayed_count;
        } else {
            if(word->GetArtikel() == word->GetUserArtikel()) {
                ++correct_count;
            } else {
                ++incorrect_count;
            }
        }

    }

    double score = (double)(correct_count - (incorrect_count/2.0))/count;

    result.UpdateResult(score,correct_count, incorrect_count, unplayed_count);

    Result_C::GRADE grade = result.Grade();
    if(grade >= Result_C::GRADE_AP) {
        thema.AddExperiencePoints(80);
    } else if(grade >= Result_C::GRADE_A) {
        thema.AddExperiencePoints(60);
    } else if (grade >= Result_C::GRADE_BP) {
        thema.AddExperiencePoints(50);
    } else if (grade >= Result_C::GRADE_C) {
        thema.AddExperiencePoints(40);
    } else if(grade >= Result_C::GRADE_D){
        thema.AddExperiencePoints(30);
    } else {
        thema.DeductExperiencePoints(2);
    }

}

