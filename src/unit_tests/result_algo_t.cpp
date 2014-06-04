#include <QString>
#include <QtTest>
#include <QGuiApplication>

#include "data/thema.h"
#include "data/word.h"
#include "data/result.h"
#include "der_artikel/algo/easy_result_algo.h"

static const uint WORD_SAMPLE_SIZE =100;

class ResultAlgo_T : public QObject
{
    Q_OBJECT

public:
    ResultAlgo_T();

private Q_SLOTS:
    void initTestCase();
    void init();
    void testThema();
    void testEasyResultAlgo();
    void cleanup();
    void cleanupTestCase();

private:
    Thema_C* _test_thema;
    int _correct_word_count;
    int _incorrect_word_count;
    int _unplayed_word_count;
};

ResultAlgo_T::ResultAlgo_T():
    _test_thema(0),
    _correct_word_count(0),
    _incorrect_word_count(0),
    _unplayed_word_count(0)
{
}

void ResultAlgo_T::initTestCase()
{
    int argc = 0;
    QGuiApplication a(argc,0);
    _test_thema = new Thema_C;
}

void ResultAlgo_T::init()
{
    qsrand(QTime::currentTime().msec());
    for(uint i = 0; i<WORD_SAMPLE_SIZE; ++i) {
        Word_C* word = new Word_C;
        word->_text = QString("Test word %1").arg(i);
        int random_number = qrand()%3;
        switch (random_number) {
            case 0: // Correct word.
                word->_artikel = Article_C::DER;
                word->_user_artikel = Article_C::DER;
                ++_correct_word_count;
                break;
            case 1: // Incorrect word.
                word->_artikel = Article_C::DER;
                word->_user_artikel = Article_C::DIE;
                ++_incorrect_word_count;
                break;
            case 2: // Unplayed word.
                word->_artikel = Article_C::DER;
                ++_unplayed_word_count;
                break;
            default:
                break;
        }
        _test_thema->_words.append(word);
    }
}

void ResultAlgo_T::testThema()
{
    QCOMPARE(_test_thema->wordCount(),WORD_SAMPLE_SIZE);
    QCOMPARE(_test_thema->wordCount(), uint(_unplayed_word_count + _correct_word_count + _incorrect_word_count));
}

void ResultAlgo_T::testEasyResultAlgo()
{
    EasyResultAlgo_C result_algo;
    Result_C result;
    result_algo.calculate(*_test_thema,result);
    QVERIFY(qAbs(result.score()-double(_correct_word_count)/WORD_SAMPLE_SIZE) < 0.01);
}

void ResultAlgo_T::cleanup()
{
    _test_thema->clearWords();
    _correct_word_count=0;
    _incorrect_word_count=0;
    _unplayed_word_count=0;
}

void ResultAlgo_T::cleanupTestCase()
{
    delete _test_thema;
}

QTEST_APPLESS_MAIN(ResultAlgo_T)

#include "result_algo_t.moc"
