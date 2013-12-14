#include "strict_result_algo.h"
#include "data/word.h"
#include "data/thema.h"
#include "data/result.h"


StrictResultAlgo_C::StrictResultAlgo_C():ResultAlgo_I()
{
}

void StrictResultAlgo_C::Calculate(Thema_I& thema, Result_C& result)
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

    double score = (double)(correct_count - (incorrect_words.count()/2.0) - (unplayed_count/4.0))/count;

    result.UpdateResult(score,correct_count, unplayed_count, incorrect_words);

    Result_C::GRADE grade = result.Grade();
    if(grade >= Result_C::GRADE_AP) {
        thema.AddExperiencePoints(100);
    } else if(grade >= Result_C::GRADE_A) {
        thema.AddExperiencePoints(80);
    } else if (grade >= Result_C::GRADE_BP) {
        thema.AddExperiencePoints(70);
    } else if (grade >= Result_C::GRADE_C) {
        thema.AddExperiencePoints(60);
    } else if(grade >= Result_C::GRADE_D){
        thema.AddExperiencePoints(40);
    } else {
        thema.DeductExperiencePoints(20);
    }

}
