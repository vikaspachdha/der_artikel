#include <QString>
#include <QtTest>

#include "data/thema.h"
#include "result_algo_t.h"
#include "data/word.h"
#include "data/result.h"
#include "der_artikel/algo/easy_result_algo.h"
#include "der_artikel/algo/moderate_result_algo.h"
#include "der_artikel/algo/strict_result_algo.h"

static const uint WORD_SAMPLE_SIZE = 100;
static const double UNPLAYED_RATIO = 0.3;

ResultAlgo_T::ResultAlgo_T():
    _thema_100_percent(0),
    _thema_95_percent(0),
    _thema_90_percent(0),
    _thema_80_percent(0),
    _thema_70_percent(0),
    _thema_60_percent(0),
    _thema_50_percent(0),
    _thema_40_percent(0)
{
}

void ResultAlgo_T::initTestCase()
{
    _thema_100_percent = new Thema_C;
    _thema_95_percent = new Thema_C;
    _thema_90_percent = new Thema_C;
    _thema_80_percent = new Thema_C;
    _thema_70_percent = new Thema_C;
    _thema_60_percent = new Thema_C;
    _thema_50_percent = new Thema_C;
    _thema_40_percent = new Thema_C;
}

void ResultAlgo_T::init()
{
    populateThema(*_thema_100_percent, 1.0, UNPLAYED_RATIO);
    populateThema(*_thema_95_percent, 0.95, UNPLAYED_RATIO);
    populateThema(*_thema_90_percent, 0.90, UNPLAYED_RATIO);
    populateThema(*_thema_80_percent, 0.80, UNPLAYED_RATIO);
    populateThema(*_thema_70_percent, 0.70, UNPLAYED_RATIO);
    populateThema(*_thema_60_percent, 0.60, UNPLAYED_RATIO);
    populateThema(*_thema_50_percent, 0.50, UNPLAYED_RATIO);
    populateThema(*_thema_40_percent, 0.40, UNPLAYED_RATIO);
}

void ResultAlgo_T::testThemaConsistancy()
{
    uint correct_word_count;
    uint unplayed_word_count;
    uint incorrect_word_count;
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 1.0, 0.0);

    QCOMPARE(_thema_100_percent->wordCount(),WORD_SAMPLE_SIZE);
    QCOMPARE(_thema_95_percent->wordCount(),WORD_SAMPLE_SIZE);
    QCOMPARE(_thema_90_percent->wordCount(),WORD_SAMPLE_SIZE);
    QCOMPARE(_thema_80_percent->wordCount(),WORD_SAMPLE_SIZE);
    QCOMPARE(_thema_70_percent->wordCount(),WORD_SAMPLE_SIZE);
    QCOMPARE(_thema_60_percent->wordCount(),WORD_SAMPLE_SIZE);
    QCOMPARE(_thema_50_percent->wordCount(),WORD_SAMPLE_SIZE);
    QCOMPARE(_thema_40_percent->wordCount(),WORD_SAMPLE_SIZE);


    QCOMPARE(_thema_100_percent->wordCount(), unplayed_word_count + correct_word_count + incorrect_word_count);
    QCOMPARE(_thema_95_percent->wordCount(), unplayed_word_count + correct_word_count + incorrect_word_count);
    QCOMPARE(_thema_90_percent->wordCount(), unplayed_word_count + correct_word_count + incorrect_word_count);
    QCOMPARE(_thema_80_percent->wordCount(), unplayed_word_count + correct_word_count + incorrect_word_count);
    QCOMPARE(_thema_70_percent->wordCount(), unplayed_word_count + correct_word_count + incorrect_word_count);
    QCOMPARE(_thema_60_percent->wordCount(), unplayed_word_count + correct_word_count + incorrect_word_count);
    QCOMPARE(_thema_50_percent->wordCount(), unplayed_word_count + correct_word_count + incorrect_word_count);
    QCOMPARE(_thema_40_percent->wordCount(), unplayed_word_count + correct_word_count + incorrect_word_count);
}

void ResultAlgo_T::testEasyResultAlgo()
{
    EasyResultAlgo_C result_algo;
    uint correct_word_count;
    uint unplayed_word_count;
    uint incorrect_word_count;
    Result_C result;

    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 1.0, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_100_percent,result);
    QVERIFY2(qAbs(result.score()-1.0) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(1.0).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_AP, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_AP).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == 50, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(50).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.95, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_95_percent,result);
    QVERIFY2(qAbs(result.score()-0.95) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.95).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_AP, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_AP).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == 50, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(50).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.90, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_90_percent,result);
    QVERIFY2(qAbs(result.score()-0.90) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.90).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_A, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_A).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == 40, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(40).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.80, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_80_percent,result);
    QVERIFY2(qAbs(result.score()-0.80) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.80).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_BP, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_BP).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == 30, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(30).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.70, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_70_percent,result);
    QVERIFY2(qAbs(result.score()-0.70) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.70).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_B, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_B).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == 20, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(20).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.60, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_60_percent,result);
    QVERIFY2(qAbs(result.score()-0.60) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.60).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_C, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_C).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == 10, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(10).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.50, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_50_percent,result);
    QVERIFY2(qAbs(result.score()-0.50) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.50).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_D, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_D).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == 5, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(5).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.40, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_40_percent,result);
    QVERIFY2(qAbs(result.score()-0.40) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.40).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_E, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_E).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == 0, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(0).toLatin1());

    QVERIFY2(result_algo.playTime(*_thema_100_percent) == WORD_SAMPLE_SIZE*4, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_100_percent) ).arg(WORD_SAMPLE_SIZE*4).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_95_percent) == WORD_SAMPLE_SIZE*4, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_95_percent) ).arg(WORD_SAMPLE_SIZE*4).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_90_percent) == WORD_SAMPLE_SIZE*4, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_90_percent) ).arg(WORD_SAMPLE_SIZE*4).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_80_percent) == WORD_SAMPLE_SIZE*4, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_80_percent) ).arg(WORD_SAMPLE_SIZE*4).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_70_percent) == WORD_SAMPLE_SIZE*4, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_70_percent) ).arg(WORD_SAMPLE_SIZE*4).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_60_percent) == WORD_SAMPLE_SIZE*4, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_60_percent) ).arg(WORD_SAMPLE_SIZE*4).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_50_percent) == WORD_SAMPLE_SIZE*4, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_50_percent) ).arg(WORD_SAMPLE_SIZE*4).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_40_percent) == WORD_SAMPLE_SIZE*4, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_40_percent) ).arg(WORD_SAMPLE_SIZE*4).toLatin1());

}

void ResultAlgo_T::testModerateResultAlgo()
{
    ModerateResultAlgo_C result_algo;
    uint correct_word_count;
    uint unplayed_word_count;
    uint incorrect_word_count;
    Result_C result;

    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 1.0, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_100_percent,result);
    QVERIFY2(qAbs(result.score()-1.0) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(1.0).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_AP, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_AP).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == 80, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(80).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.95, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_95_percent,result);
    QVERIFY2(qAbs(result.score()-0.935) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.935).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_A, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_A).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == 60, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(60).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.90, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_90_percent,result);
    QVERIFY2(qAbs(result.score()-0.865) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.865).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_BP, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_BP).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == 50, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(50).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.80, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_80_percent,result);
    QVERIFY2(qAbs(result.score()-0.73) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.73).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_B, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_B).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == 40, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(40).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.70, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_70_percent,result);
    QVERIFY2(qAbs(result.score()-0.595) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.595).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_D, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_D).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == 20, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(20).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.60, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_60_percent,result);
    QVERIFY2(qAbs(result.score()-0.46) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.46).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_E, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_E).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == -10, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(-10).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.50, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_50_percent,result);
    QVERIFY2(qAbs(result.score()-0.325) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.325).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_E, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_E).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == -10, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(-10).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.40, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_40_percent,result);
    QVERIFY2(qAbs(result.score()-0.19) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.19).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_E, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_E).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == -10, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(-10).toLatin1());

    QVERIFY2(result_algo.playTime(*_thema_100_percent) == WORD_SAMPLE_SIZE*3, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_100_percent) ).arg(WORD_SAMPLE_SIZE*3).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_95_percent) == WORD_SAMPLE_SIZE*3, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_95_percent) ).arg(WORD_SAMPLE_SIZE*3).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_90_percent) == WORD_SAMPLE_SIZE*3, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_90_percent) ).arg(WORD_SAMPLE_SIZE*3).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_80_percent) == WORD_SAMPLE_SIZE*3, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_80_percent) ).arg(WORD_SAMPLE_SIZE*3).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_70_percent) == WORD_SAMPLE_SIZE*3, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_70_percent) ).arg(WORD_SAMPLE_SIZE*3).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_60_percent) == WORD_SAMPLE_SIZE*3, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_60_percent) ).arg(WORD_SAMPLE_SIZE*3).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_50_percent) == WORD_SAMPLE_SIZE*3, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_50_percent) ).arg(WORD_SAMPLE_SIZE*3).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_40_percent) == WORD_SAMPLE_SIZE*3, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_40_percent) ).arg(WORD_SAMPLE_SIZE*3).toLatin1());

}

void ResultAlgo_T::testStrictResultAlgo()
{
    StrictResultAlgo_C result_algo;
    uint correct_word_count;
    uint unplayed_word_count;
    uint incorrect_word_count;
    Result_C result;

    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 1.0, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_100_percent,result);
    QVERIFY2(qAbs(result.score()-1.0) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(1.0).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_AP, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_AP).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == 100, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(100).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.95, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_95_percent,result);
    QVERIFY2(qAbs(result.score()-0.93) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.93).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_A, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_A).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == 80, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(80).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.90, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_90_percent,result);
    QVERIFY2(qAbs(result.score()-0.8625) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.8625).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_BP, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_BP).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == 70, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(70).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.80, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_80_percent,result);
    QVERIFY2(qAbs(result.score()-0.715) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.715).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_B, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_B).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == 60, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(60).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.70, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_70_percent,result);
    QVERIFY2(qAbs(result.score()-0.5725) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.5725).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_D, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_D).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == 40, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(40).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.60, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_60_percent,result);
    QVERIFY2(qAbs(result.score()-0.43) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.43).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_E, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_E).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == -20, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(-20).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.50, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_50_percent,result);
    QVERIFY2(qAbs(result.score()-0.2875) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.2875).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_E, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_E).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == -20, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(-20).toLatin1());

    result.clear();
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, 0.40, UNPLAYED_RATIO);
    result_algo.calculate(*_thema_40_percent,result);
    QVERIFY2(qAbs(result.score()-0.145) < 0.01, QString(" score : %1, Expected : %2").arg(result.score()).arg(0.145).toLatin1());
    QVERIFY2(result.grade() == Result_C::GRADE_E, QString(" Grade : %1, Expected : %2").arg(result.grade()).arg(Result_C::GRADE_E).toLatin1());
    QVERIFY2(result.correctWordCount() == correct_word_count, QString(" correctWordCount : %1, Expected : %2").arg(result.correctWordCount()).arg(correct_word_count).toLatin1());
    QVERIFY2(result.mistakesCount() == incorrect_word_count, QString(" mistakesCount : %1, Expected : %2").arg(result.mistakesCount()).arg(incorrect_word_count).toLatin1());
    QVERIFY2(result.unplayedCount() == unplayed_word_count, QString(" unplayedCount : %1, Expected : %2").arg(result.unplayedCount()).arg(unplayed_word_count).toLatin1());
    QVERIFY2(result.experienceChange() == -20, QString(" experienceChange : %1, Expected : %2").arg(result.experienceChange()).arg(-20).toLatin1());

    QVERIFY2(result_algo.playTime(*_thema_100_percent) == WORD_SAMPLE_SIZE*2, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_100_percent) ).arg(WORD_SAMPLE_SIZE*2).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_95_percent) == WORD_SAMPLE_SIZE*2, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_95_percent) ).arg(WORD_SAMPLE_SIZE*2).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_90_percent) == WORD_SAMPLE_SIZE*2, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_90_percent) ).arg(WORD_SAMPLE_SIZE*2).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_80_percent) == WORD_SAMPLE_SIZE*2, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_80_percent) ).arg(WORD_SAMPLE_SIZE*2).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_70_percent) == WORD_SAMPLE_SIZE*2, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_70_percent) ).arg(WORD_SAMPLE_SIZE*2).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_60_percent) == WORD_SAMPLE_SIZE*2, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_60_percent) ).arg(WORD_SAMPLE_SIZE*2).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_50_percent) == WORD_SAMPLE_SIZE*2, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_50_percent) ).arg(WORD_SAMPLE_SIZE*2).toLatin1());
    QVERIFY2(result_algo.playTime(*_thema_40_percent) == WORD_SAMPLE_SIZE*2, QString(" Playtime : %1, Expected : %2").arg(result_algo.playTime(*_thema_40_percent) ).arg(WORD_SAMPLE_SIZE*2).toLatin1());

}

void ResultAlgo_T::cleanup()
{
    _thema_100_percent->resetThema();
    _thema_95_percent->resetThema();
    _thema_90_percent->resetThema();
    _thema_80_percent->resetThema();
    _thema_70_percent->resetThema();
    _thema_60_percent->resetThema();
    _thema_50_percent->resetThema();
    _thema_40_percent->resetThema();
}

void ResultAlgo_T::cleanupTestCase()
{
    delete _thema_100_percent;
    delete _thema_95_percent;
    delete _thema_90_percent;
    delete _thema_80_percent;
    delete _thema_70_percent;
    delete _thema_60_percent;
    delete _thema_50_percent;
    delete _thema_40_percent;
}

void ResultAlgo_T::populateThema(Thema_C& thema, double correct_percentage, double unplayed_share)
{
    uint correct_word_count;
    uint unplayed_word_count;
    uint incorrect_word_count;
    wordsCount(correct_word_count, incorrect_word_count, unplayed_word_count, correct_percentage, unplayed_share);

    // Add Correct words.
    for(uint i = 0; i<correct_word_count; ++i) {
        Word_C* word = new Word_C;
        word->_text = QString("Correct word %1").arg(i);
        word->_artikel = Article_C::DER;
        word->_user_artikel = Article_C::DER;
        thema._words.append(word);
    }

    // Add incorrect words.
    for(uint i = 0; i<incorrect_word_count; ++i) {
        Word_C* word = new Word_C;
        word->_text = QString("incorrect word %1").arg(i);
        word->_artikel = Article_C::DER;
        word->_user_artikel = Article_C::DIE;
        thema._words.append(word);
    }

    // Add unplayed words.
    for(uint i = 0; i<unplayed_word_count; ++i) {
        Word_C* word = new Word_C;
        word->_text = QString("unplayed word %1").arg(i);
        word->_artikel = Article_C::DER;
        thema._words.append(word);
    }
}

void ResultAlgo_T::wordsCount(uint &correct_word_count, uint &incorrect_word_count, uint &unplayed_word_count, double correct_percentage, double unplayed_share)
{
   correct_word_count = (uint)qRound(correct_percentage * WORD_SAMPLE_SIZE);
   unplayed_word_count = (uint)qRound((WORD_SAMPLE_SIZE - correct_word_count) * unplayed_share);
   incorrect_word_count = WORD_SAMPLE_SIZE - correct_word_count - unplayed_word_count;
}
