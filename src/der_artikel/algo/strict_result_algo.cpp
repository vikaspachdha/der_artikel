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
    unsigned int incorrect_count = 0;
    unsigned int unplayed_count = 0;

    for(unsigned int index = 0; index < count; ++index) {
        const Word_C* word = thema.GetWord(index);
        if(word->GetUserArtikel() == ARTIKEL::INVALID || word->GetUserArtikel() == ARTIKEL::NA) {
            ++unplayed_count;
        } else {
            if(word->GetArtikel() == word->GetUserArtikel()) {
                ++correct_count;
            } else {
                ++incorrect_count;
            }
        }

    }

    double score = (double)(correct_count - (incorrect_count/2.0) - (unplayed_count/4.0))/count;

    result.SetScore(score);
    result.SetCorrectWordCount(correct_count);
    result.SetMistakesCount(incorrect_count);
    result.SetUnplayedCount(unplayed_count);
}
