cache()
QT += xml widgets network

DEFINES += ENABLE_THEMA_BUILDER

# Add more folders to ship with the application, here
folder_01.source = thema
folder_01.target = ./
DEPLOYMENTFOLDERS = folder_01

folder_02.source = languages
folder_02.target = ./
DEPLOYMENTFOLDERS += folder_02

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    manager.cpp \
    data/word.cpp \
    data/thema.cpp \
    thema_builder.cpp \
    common.cpp \
    thema_loader.cpp \
    algo/strict_result_algo.cpp \
    data/result.cpp \
    thema_model.cpp \
    article.cpp \
    algo/easy_result_algo.cpp \
    algo/moderate_result_algo.cpp \
    word_model.cpp \
    pages/home_page.cpp \
    pages/page.cpp \
    pages/settings_page.cpp \
    pages/help_page.cpp \
    pages/words_page.cpp \
    pages/stats_page.cpp \
    settings.cpp \
    pages/thema_page.cpp \
    conflict_dlg.cpp \
    image_provider.cpp \
    file_downloader.cpp \
    thema_updater.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    manager.h \
    data/word.h \
    common.h \
    data/thema.h \
    thema_builder.h \
    thema_loader.h \
    version.h \
    algo/strict_result_algo.h \
    algo/result_algo.h \
    data/result.h \
    data/thema_interface.h \
    thema_model.h \
    article.h \
    algo/easy_result_algo.h \
    algo/moderate_result_algo.h \
    word_model.h \
    pages/home_page.h \
    pages/page_i.h \
    pages/page.h \
    pages/settings_page.h \
    pages/help_page.h \
    pages/words_page.h \
    pages/stats_page.h \
    settings.h \
    pages/thema_page.h \
    conflict_dlg.h \
    image_provider.h \
    file_downloader.h \
    thema_updater.h

FORMS += \
    thema_builder.ui \
    conflict_dlg.ui

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
