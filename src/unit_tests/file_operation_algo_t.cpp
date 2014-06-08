#include <QDir>
#include <QTest>

#include "file_operation_algo_t.h"

#include "../data/thema.h"
#include "../data/thema_loader.h"
#include "der_artikel/algo/thema_add_operation.h"
#include "der_artikel/algo/thema_delete_operation.h"
#include "der_artikel/algo/thema_replace_operation.h"

static const QString FILE_NAME = "test_thema.AKL";
static const QString SRC_DIR = QDir::tempPath() + "/file_algo_test_src/";
static const QString SRC_FILE = SRC_DIR +FILE_NAME;
static const QString TARGET_DIR = QDir::tempPath() + "/file_algo_test_target/";
static const QString TARGET_FILE = TARGET_DIR + FILE_NAME;

static const QString THEMA_NAME = "Test thema";
static const QString AUTHOR = "Vikas";
static const QString TR_NAME = "Test thema translation";
static const uint WORD_SAMPLE_SIZE = 10;

FileOperationAlgo_T::FileOperationAlgo_T(QObject *parent) :
    QObject(parent)
{
}

void FileOperationAlgo_T::initTestCase()
{
    _test_thema = new Thema_C;
}

void FileOperationAlgo_T::init()
{
    QDir tempFolder(QDir::tempPath());
    tempFolder.mkdir("file_algo_test_src");
    tempFolder.mkdir("file_algo_test_target");

    _test_thema->resetThema();
    _test_thema->_author = AUTHOR;
    _test_thema->_text = THEMA_NAME;
    _test_thema->_translation = TR_NAME;
    _test_thema->_file_path = SRC_FILE;
    // Add Correct words.
    for(uint i = 0; i<WORD_SAMPLE_SIZE; ++i) {
        Word_C* word = new Word_C;
        word->_text = QString("Correct word %1").arg(i);
        word->_artikel = Article_C::DER;
        word->_user_artikel = Article_C::DER;
        _test_thema->_words.append(word);
    }

    QVERIFY(_test_thema->save());

    QVERIFY(QFile::exists(SRC_FILE));
}

void FileOperationAlgo_T::testAddOperation()
{
    ThemaAddOperation_C addOperation(TARGET_FILE,QUrl::fromUserInput(SRC_FILE));
    addOperation.execute();
    QVERIFY(QFile::exists(TARGET_FILE));

    ThemaLoader_C thema_loader;
    Thema_C* loaded_thema = thema_loader.loadThema(TARGET_FILE,false);

    QVERIFY(loaded_thema);

    QVERIFY2(loaded_thema->author() == AUTHOR,
             QString("Thema author : %1, Expected : %2")
             .arg(loaded_thema->author())
             .arg(AUTHOR).toLatin1());

    QVERIFY2(loaded_thema->name() == THEMA_NAME,
             QString("Thema name : %1, Expected : %2")
             .arg(loaded_thema->name()).arg(THEMA_NAME).toLatin1());

    QVERIFY2(loaded_thema->trName() == TR_NAME,
             QString("Thema tr name : %1, Expected : %2").
             arg(loaded_thema->trName()).arg(TR_NAME).toLatin1());

    QVERIFY2(loaded_thema->wordCount() == WORD_SAMPLE_SIZE,
             QString("Thema word count : %1, Expected : %2")
             .arg(loaded_thema->wordCount()).arg(WORD_SAMPLE_SIZE).toLatin1());

    delete loaded_thema;
}

void FileOperationAlgo_T::testDeleteOperation()
{
    QVERIFY(QFile::exists(SRC_FILE));
    ThemaDeleteOperation_C deleteOperation(SRC_FILE);
    deleteOperation.execute();
    QVERIFY(!QFile::exists(SRC_FILE));
}

void FileOperationAlgo_T::testReplaceOperation()
{
    _test_thema->_file_path = TARGET_FILE;
    QVERIFY(_test_thema->save());

    ThemaReplaceOperation_C replaceOperation(TARGET_FILE,QUrl::fromUserInput(SRC_FILE),10);
    replaceOperation.execute();
    QVERIFY(QFile::exists(TARGET_FILE));

    ThemaLoader_C thema_loader;
    Thema_C* loaded_thema = thema_loader.loadThema(TARGET_FILE,false);

    QVERIFY(loaded_thema);

    QVERIFY2(loaded_thema->author() == AUTHOR,
             QString("Thema author : %1, Expected : %2")
             .arg(loaded_thema->author())
             .arg(AUTHOR).toLatin1());

    QVERIFY2(loaded_thema->name() == THEMA_NAME,
             QString("Thema name : %1, Expected : %2")
             .arg(loaded_thema->name()).arg(THEMA_NAME).toLatin1());

    QVERIFY2(loaded_thema->trName() == TR_NAME,
             QString("Thema tr name : %1, Expected : %2").
             arg(loaded_thema->trName()).arg(TR_NAME).toLatin1());

    QVERIFY2(loaded_thema->wordCount() == WORD_SAMPLE_SIZE,
             QString("Thema word count : %1, Expected : %2")
             .arg(loaded_thema->wordCount()).arg(WORD_SAMPLE_SIZE).toLatin1());

    QVERIFY2(loaded_thema->experiencePoints() == 10,
             QString("Thema experience : %1, Expected : %2")
             .arg(loaded_thema->experiencePoints()).arg(10).toLatin1());

    delete loaded_thema;
}

void FileOperationAlgo_T::cleanup()
{
    QDir src_dir(SRC_DIR);
    src_dir.removeRecursively();

    QDir target_dir(TARGET_DIR);
    target_dir.removeRecursively();
}

void FileOperationAlgo_T::cleanupTestCase()
{
    delete _test_thema;
}
