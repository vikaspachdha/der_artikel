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
cache()

QT += xml widgets

MOC_DIR      = moc
RCC_DIR      = resources
OBJECTS_DIR  = obj
TARGET = thema_builder
TEMPLATE = app
CONFIG(debug,debug|release):DESTDIR=$${OUT_PWD}/bin_debug
CONFIG(release,debug|release):DESTDIR=$${OUT_PWD}/bin_release


include($$PWD/../data/data.pri)

SOURCES += main.cpp \
    thema_builder.cpp \
    conflict_dlg.cpp \
    word_list_item.cpp

HEADERS += \
    thema_builder.h \
    conflict_dlg.h \
    word_list_item.h

FORMS += \
    thema_builder.ui \
    conflict_dlg.ui

RESOURCES += \
    resources.qrc

mac {
    LIBS += -L$${DESTDIR}/$${TARGET}.app/Contents/MacOS -llog4qt
    LIBS += -L$${DESTDIR}/$${TARGET}.app/Contents/MacOS -laes
} else {
    LIBS += -L$$DESTDIR -llog4qt -laes
}

INCLUDEPATH += ./ \
    $${PWD}/../libs/log4qt \
    $${PWD}/../libs/tiny_aes

# Copy log4Qt files to build dir
SOURCE_PATH = $${DESTDIR}/../../libs/log4qt
CONFIG(debug,debug|release):SOURCE_PATH = $${SOURCE_PATH}/bin_debug/*log4qt.*
CONFIG(release,debug|release):SOURCE_PATH = $${SOURCE_PATH}/bin_release/*log4qt.*
TARGET_PATH = $$DESTDIR
win32{
    SOURCE_PATH ~= s,/,\\,g
    TARGET_PATH ~= s,/,\\,g
}else:mac{
    TARGET_PATH = $${TARGET_PATH}/$${TARGET}.app/Contents/MacOS
}
QMAKE_PRE_LINK += $$QMAKE_COPY $$quote($$SOURCE_PATH) $$quote($$TARGET_PATH) $$escape_expand(\\n\\t)

# Copy tiny aes files to build dir
SOURCE_PATH = $${DESTDIR}/../../libs/tiny_aes
CONFIG(debug,debug|release):SOURCE_PATH = $${SOURCE_PATH}/bin_debug/*aes.*
CONFIG(release,debug|release):SOURCE_PATH = $${SOURCE_PATH}/bin_release/*aes.*
TARGET_PATH = $$DESTDIR
win32{
    SOURCE_PATH ~= s,/,\\,g
    TARGET_PATH ~= s,/,\\,g
}else:mac{
    TARGET_PATH = $${TARGET_PATH}/$${TARGET}.app/Contents/MacOS
}
QMAKE_PRE_LINK += $$QMAKE_COPY $$quote($$SOURCE_PATH) $$quote($$TARGET_PATH) $$escape_expand(\\n\\t)

