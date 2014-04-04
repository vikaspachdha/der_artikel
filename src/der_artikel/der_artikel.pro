cache()

DEFINES += ENABLE_THEMA_BUILDER

win32:DEFINES += NO_GRAPHICAL_EFFECTS

QT += xml widgets network

MOC_DIR      = moc
RCC_DIR      = resources
OBJECTS_DIR  = obj
TARGET = der_artikel
TEMPLATE = app
CONFIG(debug,debug|release):DESTDIR=$${OUT_PWD}/bin_debug
CONFIG(release,debug|release):DESTDIR=$${OUT_PWD}/bin_release

include($$PWD/../data/data.pri)

SOURCES += main.cpp \
    manager.cpp \
    algo/strict_result_algo.cpp \
    thema_model.cpp \
    algo/easy_result_algo.cpp \
    algo/moderate_result_algo.cpp \
    pages/home_page.cpp \
    pages/page.cpp \
    pages/settings_page.cpp \
    pages/help_page.cpp \
    pages/words_page.cpp \
    pages/stats_page.cpp \
    settings.cpp \
    pages/thema_page.cpp \
    image_provider.cpp \
    file_downloader.cpp \
    thema_updater.cpp \
    algo/thema_replace_operation.cpp \
    algo/thema_add_operation.cpp \
    algo/thema_delete_operation.cpp

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)


HEADERS += \
    manager.h \
    algo/strict_result_algo.h \
    algo/result_algo.h \
    thema_model.h \
    algo/easy_result_algo.h \
    algo/moderate_result_algo.h \
    pages/home_page.h \
    pages/page_i.h \
    pages/page.h \
    pages/settings_page.h \
    pages/help_page.h \
    pages/words_page.h \
    pages/stats_page.h \
    settings.h \
    pages/thema_page.h \
    image_provider.h \
    file_downloader.h \
    thema_updater.h \
    algo/thema_replace_operation.h \
    algo/thema_file_operation.h \
    algo/thema_add_operation.h \
    algo/thema_delete_operation.h

RESOURCES += \
    resources.qrc

# Lupdate cosiders files added under SOURCES variable only.
hack_for_qml_lupdate {
    SOURCES += qml/der_artikel/*.qml
}

TRANSLATIONS += ./der_artikel_de.ts \
    ./der_artikel_en.ts \
    ./der_artikel_hin.ts

OTHER_FILES += ./der_artikel_de.ts \
    ./der_artikel_en.ts \
    ./der_artikel_hin.ts

# Add more folders to ship with the application, here
folder_01.source = thema
folder_01.target =
DEPLOYMENTFOLDERS += folder_01

folder_02.source = languages
folder_02.target =
DEPLOYMENTFOLDERS += folder_02
qtcAddDeployment()

mac {
    LIBS += -L$${DESTDIR}/$${TARGET}.app/Contents/MacOS -llog4qt
} else {
    LIBS += -L$$DESTDIR -llog4Qt
}

INCLUDEPATH += $$PWD/../libs/log4qt
DEPENDPATH += $${PWD}/../libs/log4qt

# Copy files to build dir
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

