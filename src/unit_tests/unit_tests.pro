#******************************************************************************
#   \author Vikas Pachdha
# 
#   \copyright Copyright (C) 2014 Vikas Pachdha, Mohita Gandotra.
#  Contact: http://www.vikaspachdha.com
# 
#  This file is part of the application der_artikel.
# 
#   \copyright GNU Lesser General Public License Usage
#  This file may be used under the terms of the GNU Lesser
#  General Public License version 2.1 as published by the Free Software
#  Foundation and appearing in the file LICENSE.LGPL included in the
#  packaging of this file.  Please review the following information to
#  ensure the GNU Lesser General Public License version 2.1 requirements
#  will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
# 
#   \copyright GNU General Public License Usage
#  Alternatively, this file may be used under the terms of the GNU
#  General Public License version 3.0 as published by the Free Software
#  Foundation and appearing in the file LICENSE.GPL included in the
#  packaging of this file.  Please review the following information to
#  ensure the GNU General Public License version 3.0 requirements will be
#  met: http://www.gnu.org/copyleft/gpl.html.
# 
#*****************************************************************************/
#-------------------------------------------------
#
# Project created by QtCreator 2014-06-02T02:20:06
#
#-------------------------------------------------

QT       += core testlib xml gui network

TARGET = unit_tests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG(debug,debug|release):DESTDIR=$${OUT_PWD}/bin_debug
CONFIG(release,debug|release):DESTDIR=$${OUT_PWD}/bin_release

HEADERS += \
    ../data/article.h \
    ../data/common.h \
    ../data/result.h \
    ../data/thema.h \
    ../data/thema_loader.h \
    ../data/word.h \
    ../data/word_model.h \
    ../der_artikel/algo/easy_result_algo.h \
    ../der_artikel/algo/moderate_result_algo.h \
    ../der_artikel/algo/result_algo.h \
    ../der_artikel/algo/strict_result_algo.h \
    ../der_artikel/algo/thema_add_operation.h \
    ../der_artikel/algo/thema_delete_operation.h \
    ../der_artikel/algo/thema_file_operation.h \
    ../der_artikel/algo/thema_replace_operation.h \
    ../der_artikel/file_downloader.h \
    file_operation_algo_t.h \
    log4qt/log_defines.h \
    result_algo_t.h


SOURCES += \
    ../data/article.cpp \
    ../data/common.cpp \
    ../data/result.cpp \
    ../data/thema.cpp \
    ../data/thema_loader.cpp \
    ../data/word.cpp \
    ../data/word_model.cpp \
    ../der_artikel/algo/easy_result_algo.cpp \
    ../der_artikel/algo/moderate_result_algo.cpp \
    ../der_artikel/algo/strict_result_algo.cpp \
    ../der_artikel/algo/thema_add_operation.cpp \
    ../der_artikel/algo/thema_delete_operation.cpp \
    ../der_artikel/algo/thema_replace_operation.cpp \
    ../der_artikel/file_downloader.cpp \
    file_operation_algo_t.cpp \
    result_algo_t.cpp \
    test_main.cpp


DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += ./ \
    ../ \
    ../der_artikel \
    $${PWD}/../libs/tiny_aes

# Copy tiny aes files to build dir
SOURCE_PATH = $${DESTDIR}/../../libs/tiny_aes
CONFIG(debug,debug|release):SOURCE_PATH = $${SOURCE_PATH}/bin_debug/*aes.*
CONFIG(release,debug|release):SOURCE_PATH = $${SOURCE_PATH}/bin_release/*aes.*
TARGET_PATH = $$DESTDIR
win32{
    SOURCE_PATH ~= s,/,\\,g
    TARGET_PATH ~= s,/,\\,g
}
QMAKE_PRE_LINK += $$QMAKE_COPY $$quote($$SOURCE_PATH) $$quote($$TARGET_PATH) $$escape_expand(\\n\\t)
