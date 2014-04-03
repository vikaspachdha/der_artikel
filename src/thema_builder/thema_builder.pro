cache()

QT += xml widgets

MOC_DIR      = moc
RCC_DIR      = resources
OBJECTS_DIR  = obj
TARGET = thema_builder
TEMPLATE = app
DESTDIR  = $${OUT_PWD}
include($$PWD/../data/data.pri)



SOURCES += main.cpp \
    thema_builder.cpp \
    conflict_dlg.cpp

HEADERS += \
    thema_builder.h \
    conflict_dlg.h

FORMS += \
    thema_builder.ui \
    conflict_dlg.ui

RESOURCES += \
    resources.qrc

mac {
    LIBS += -L$${DESTDIR}/$${TARGET}.app/Contents/MacOS -llog4Qt
} else {
    LIBS += -L$$DESTDIR -llog4Qt
}

INCLUDEPATH += $$PWD/../libs/log4qt
DEPENDPATH += $${PWD}/../libs/log4qt

# Copy files to build dir
SOURCE_PATH = $${DESTDIR}/../libs/log4qt/*.dylib
TARGET_PATH = $$DESTDIR
win32{
    SOURCE_PATH ~= s,/,\\,g
    TARGET_PATH ~= s,/,\\,g
}else:mac{
    TARGET_PATH = $${TARGET_PATH}/$${TARGET}.app/Contents/MacOS
}
QMAKE_PRE_LINK += $$QMAKE_COPY $$quote($$SOURCE_PATH) $$quote($$TARGET_PATH) $$escape_expand(\\n\\t)

