#-------------------------------------------------
#
# Project created by QtCreator 2014-03-16T00:57:32
#
#-------------------------------------------------

QT       += core
MOC_DIR      = moc
RCC_DIR      = resources
OBJECTS_DIR  = obj
TARGET = log4qt
TEMPLATE = lib
CONFIG(debug,debug|release):DESTDIR=$${OUT_PWD}/bin_debug
CONFIG(release,debug|release):DESTDIR=$${OUT_PWD}/bin_release
CONFIG += shared

DEFINES += LOG4QT_LIBRARY

INCLUDEPATH += ./

HEADERS += \
    $$PWD/log4qt/appender.h \
    $$PWD/log4qt/appenderskeleton.h \
    $$PWD/log4qt/basicconfigurator.h \
    $$PWD/log4qt/consoleappender.h \
    $$PWD/log4qt/dailyrollingfileappender.h \
    $$PWD/log4qt/fileappender.h \
    $$PWD/log4qt/helpers/classlogger.h \
    $$PWD/log4qt/helpers/configuratorhelper.h \
    $$PWD/log4qt/helpers/datetime.h \
    $$PWD/log4qt/helpers/factory.h \
    $$PWD/log4qt/helpers/initialisationhelper.h \
    $$PWD/log4qt/helpers/logerror.h \
    $$PWD/log4qt/helpers/logobject.h \
    $$PWD/log4qt/helpers/logobjectptr.h \
    $$PWD/log4qt/helpers/optionconverter.h \
    $$PWD/log4qt/helpers/patternformatter.h \
    $$PWD/log4qt/helpers/properties.h \
    $$PWD/log4qt/hierarchy.h \
    $$PWD/log4qt/layout.h \
    $$PWD/log4qt/level.h \
    $$PWD/log4qt/log4qt.h \
    $$PWD/log4qt/logger.h \
    $$PWD/log4qt/loggerrepository.h \
    $$PWD/log4qt/loggingevent.h \
    $$PWD/log4qt/logmanager.h \
    $$PWD/log4qt/mdc.h \
    $$PWD/log4qt/ndc.h \
    $$PWD/log4qt/patternlayout.h \
    $$PWD/log4qt/propertyconfigurator.h \
    $$PWD/log4qt/rollingfileappender.h \
    $$PWD/log4qt/simplelayout.h \
    $$PWD/log4qt/spi/filter.h \
    $$PWD/log4qt/ttcclayout.h \
    $$PWD/log4qt/writerappender.h \
    $$PWD/log4qt/varia/debugappender.h \
    $$PWD/log4qt/varia/denyallfilter.h \
    $$PWD/log4qt/varia/nullappender.h \
    $$PWD/log4qt/varia/levelmatchfilter.h \
    $$PWD/log4qt/varia/levelrangefilter.h \
    $$PWD/log4qt/varia/listappender.h \
    $$PWD/log4qt/varia/stringmatchfilter.h \
    $$PWD/log4qt_global.h

SOURCES += \
    $$PWD/log4qt/appenderskeleton.cpp \
    $$PWD/log4qt/basicconfigurator.cpp \
    $$PWD/log4qt/consoleappender.cpp \
    $$PWD/log4qt/dailyrollingfileappender.cpp \
    $$PWD/log4qt/fileappender.cpp \
    $$PWD/log4qt/helpers/classlogger.cpp \
    $$PWD/log4qt/helpers/configuratorhelper.cpp \
    $$PWD/log4qt/helpers/datetime.cpp \
    $$PWD/log4qt/helpers/factory.cpp \
    $$PWD/log4qt/helpers/initialisationhelper.cpp \
    $$PWD/log4qt/helpers/logerror.cpp \
    $$PWD/log4qt/helpers/logobject.cpp \
    $$PWD/log4qt/helpers/logobjectptr.cpp \
    $$PWD/log4qt/helpers/optionconverter.cpp \
    $$PWD/log4qt/helpers/patternformatter.cpp \
    $$PWD/log4qt/helpers/properties.cpp \
    $$PWD/log4qt/hierarchy.cpp \
    $$PWD/log4qt/layout.cpp \
    $$PWD/log4qt/level.cpp \
    $$PWD/log4qt/log4qt.cpp \
    $$PWD/log4qt/logger.cpp \
    $$PWD/log4qt/loggerrepository.cpp \
    $$PWD/log4qt/loggingevent.cpp \
    $$PWD/log4qt/logmanager.cpp \
    $$PWD/log4qt/mdc.cpp \
    $$PWD/log4qt/ndc.cpp \
    $$PWD/log4qt/patternlayout.cpp \
    $$PWD/log4qt/propertyconfigurator.cpp \
    $$PWD/log4qt/rollingfileappender.cpp \
    $$PWD/log4qt/simplelayout.cpp \
    $$PWD/log4qt/spi/filter.cpp \
    $$PWD/log4qt/ttcclayout.cpp \
    $$PWD/log4qt/writerappender.cpp \
    $$PWD/log4qt/varia/debugappender.cpp \
    $$PWD/log4qt/varia/denyallfilter.cpp \
    $$PWD/log4qt/varia/nullappender.cpp \
    $$PWD/log4qt/varia/levelmatchfilter.cpp \
    $$PWD/log4qt/varia/levelrangefilter.cpp \
    $$PWD/log4qt/varia/listappender.cpp \
    $$PWD/log4qt/varia/stringmatchfilter.cpp
