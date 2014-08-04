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
QT       += core
QT       -= gui

MOC_DIR      = moc
RCC_DIR      = resources
OBJECTS_DIR  = obj
TARGET = aes
TEMPLATE = lib
CONFIG(debug,debug|release):DESTDIR=$${OUT_PWD}/bin_debug
CONFIG(release,debug|release):DESTDIR=$${OUT_PWD}/bin_release
CONFIG += shared
DEFINES += TINYAES_LIBRARY

SOURCES += tinyaes.cpp

HEADERS += tinyaes.h

INCLUDEPATH += ./

