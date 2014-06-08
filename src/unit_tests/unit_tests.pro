#-------------------------------------------------
#
# Project created by QtCreator 2014-06-02T02:20:06
#
#-------------------------------------------------

QT       += testlib xml gui network

TARGET = easyalgo_t
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += \
    ../data/word.h \
    ../data/word_model.h \
    ../data/thema.h \
    ../data/article.h \
    ../data/result.h \
    ../data/thema_loader.h \
    ../data/common.h \
    ../der_artikel/algo/result_algo.h \
    ../der_artikel/algo/easy_result_algo.h \
    ../der_artikel/algo/moderate_result_algo.h \
    ../der_artikel/algo/strict_result_algo.h \
    ../der_artikel/algo/thema_file_operation.h \
    ../der_artikel/algo/thema_add_operation.h \
    ../der_artikel/algo/thema_delete_operation.h \
    ../der_artikel/algo/thema_replace_operation.h \
    ../der_artikel/file_downloader.h \
    log4qt/log_defines.h \
    result_algo_t.h \
    file_operation_algo_t.h

SOURCES += \
    ../data/word.cpp \
    ../data/word_model.cpp \
    ../data/thema.cpp \
    ../data/article.cpp \
    ../data/result.cpp \
    ../data/thema_loader.cpp \
    ../data/common.cpp \
    ../der_artikel/algo/easy_result_algo.cpp \
    ../der_artikel/algo/moderate_result_algo.cpp \
    ../der_artikel/algo/strict_result_algo.cpp \
    ../der_artikel/algo/thema_add_operation.cpp \
    ../der_artikel/algo/thema_delete_operation.cpp \
    ../der_artikel/algo/thema_replace_operation.cpp \
    ../der_artikel/file_downloader.cpp \
    result_algo_t.cpp \
    main.cpp \
    file_operation_algo_t.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += ./ \
    ../ \
    ../der_artikel
