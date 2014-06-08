#ifndef FILE_OPERATION_ALGO_T_H
#define FILE_OPERATION_ALGO_T_H

#include <QObject>
class Thema_C;

class FileOperationAlgo_T : public QObject
{
    Q_OBJECT
public:
    explicit FileOperationAlgo_T(QObject *parent = 0);

private Q_SLOTS:
    void initTestCase();
    void init();
    void testAddOperation();
    void testDeleteOperation();
    void testReplaceOperation();
    void cleanup();
    void cleanupTestCase();

private:
    Thema_C* _test_thema;
};

#endif // FILE_OPERATION_ALGO_T_H
