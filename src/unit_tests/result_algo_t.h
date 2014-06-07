#ifndef RESULT_ALGO_T_H
#define RESULT_ALGO_T_H

#include <QObject>

class Thema_C;
class ResultAlgo_I;



class ResultAlgo_T : public QObject
{
    Q_OBJECT

public:
    ResultAlgo_T();

private Q_SLOTS:
    void initTestCase();
    void init();
    void testThemaConsistancy();
    void testEasyResultAlgo();
    void testModerateResultAlgo();
    void testStrictResultAlgo();
    void cleanup();
    void cleanupTestCase();

private:
    void populateThema(Thema_C &thema, double correct_percentage, double unplayed_share);
    void wordsCount(uint &correct_word_count, uint &incorrect_word_count, uint &unplayed_word_count, double correct_percentage, double unplayed_share);

private:
    Thema_C* _thema_100_percent;
    Thema_C* _thema_95_percent;
    Thema_C* _thema_90_percent;
    Thema_C* _thema_80_percent;
    Thema_C* _thema_70_percent;
    Thema_C* _thema_60_percent;
    Thema_C* _thema_50_percent;
    Thema_C* _thema_40_percent;
};

#endif // RESULT_ALGO_T_H
