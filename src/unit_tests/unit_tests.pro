#-------------------------------------------------
#
# Project created by QtCreator 2014-06-02T02:20:06
#
#-------------------------------------------------

QT       += testlib xml gui

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
    ../der_artikel/algo/result_algo.h \
    ../der_artikel/algo/easy_result_algo.h \
    ../der_artikel/algo/moderate_result_algo.h \
    ../der_artikel/algo/strict_result_algo.h \
    log4qt/log_defines.h \
    result_algo_t.h

SOURCES += \
    ../data/word.cpp \
    ../data/word_model.cpp \
    ../data/thema.cpp \
    ../data/article.cpp \
    ../data/result.cpp \
    ../der_artikel/algo/easy_result_algo.cpp \
    ../der_artikel/algo/moderate_result_algo.cpp \
    ../der_artikel/algo/strict_result_algo.cpp \
    result_algo_t.cpp \
    main.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += ./ \
    ../
