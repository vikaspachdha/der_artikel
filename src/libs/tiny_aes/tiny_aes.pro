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

