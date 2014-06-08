#include <QGuiApplication>
#include <QtTest>
#include "result_algo_t.h"
#include "file_operation_algo_t.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc,argv);

    ResultAlgo_T result_algo_test;
    QTest::qExec(&result_algo_test, argc, argv);

    FileOperationAlgo_T file_operation_algo_test;
    QTest::qExec(&file_operation_algo_test, argc, argv);

    return 0;
}
