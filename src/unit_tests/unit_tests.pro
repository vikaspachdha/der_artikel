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

HEADERS += ../data/word.h \
    ../data/thema.h \
    ../data/article.h \
    log4qt/log_defines.h

SOURCES += \
    ../data/word.cpp \
    ../data/thema.cpp \
    ../data/article.cpp \
    result_algo_t.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += ./ \
    ../
