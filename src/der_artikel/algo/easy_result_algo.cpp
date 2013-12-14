#include "easy_result_algo.h"
#include "data/word.h"
#include "data/thema.h"
#include "data/result.h"


EasyResultAlgo_C::EasyResultAlgo_C():ResultAlgo_I()
{
}

void EasyResultAlgo_C::Calculate(Thema_I& thema, Result_C& result)
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

    double score = (double)(correct_count)/count;

    result.UpdateResult(score,correct_count, unplayed_count, incorrect_words);

    Result_C::GRADE grade = result.Grade();
    if(grade >= Result_C::GRADE_AP) {
        thema.AddExperiencePoints(50);
    } else if(grade >= Result_C::GRADE_A) {
        thema.AddExperiencePoints(40);
    } else if (grade >= Result_C::GRADE_BP) {
        thema.AddExperiencePoints(30);
    } else if (grade >= Result_C::GRADE_C) {
        thema.AddExperiencePoints(20);
    } else if(grade >= Result_C::GRADE_D) {
        thema.AddExperiencePoints(10);
    }

}
