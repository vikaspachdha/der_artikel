QT += xml widgets

#DEFINES += ENABLE_THEMA_BUILDER

# Add more folders to ship with the application, here
folder_01.source = qml/der_artikel
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

folder_02.source = test_data
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
    article.cpp

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
    article.h

FORMS += \
    thema_builder.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    qml/der_artikel/Word_item.qml \
    android/AndroidManifest.xml \
    android/res/values-nl/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-et/strings.xml \
    android/res/layout/splash.xml \
    android/res/values-ru/strings.xml \
    android/res/values-es/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-zh-rTW/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/values-ro/strings.xml \
    android/version.xml \
    android/src/org/qtproject/qt5/android/bindings/QtApplication.java \
    android/src/org/qtproject/qt5/android/bindings/QtActivity.java \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl
