#include <QString>
#include <QtTest>

#include "data/thema.h"
#include "der_artikel/algo/easy_result_algo.h"

class EasyResultAlgo_T : public QObject
{
    Q_OBJECT

public:
    EasyResultAlgo_T();

private Q_SLOTS:
    void initTestCase();
    void testPlayTime();
    void testPlayTime_data();
};

EasyResultAlgo_T::EasyResultAlgo_T()
{
}

void EasyResultAlgo_T::initTestCase()
{
}

void EasyResultAlgo_T::testPlayTime()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

void EasyResultAlgo_T::testPlayTime_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

QTEST_APPLESS_MAIN(EasyResultAlgo_T)

#include "easy_result_algo_t.moc"
