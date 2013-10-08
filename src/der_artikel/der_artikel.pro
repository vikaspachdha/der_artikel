QT += xml widgets

# Add more folders to ship with the application, here
folder_01.source = qml/der_artikel
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

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
    thema_loader.cpp

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
    version.h

FORMS += \
    thema_builder.ui

RESOURCES += \
    resources.qrc
