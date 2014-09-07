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

QT += gui qml quick xml network multimedia

MOC_DIR      = moc
RCC_DIR      = resources
OBJECTS_DIR  = obj
TARGET = der_artikel
TEMPLATE = app
CONFIG(debug,debug|release):DESTDIR=$${OUT_PWD}/bin_debug
CONFIG(release,debug|release):DESTDIR=$${OUT_PWD}/bin_release

include($$PWD/../data/data.pri)
# Please do not modify the following two lines. Required for deployment.
include($$PWD/../qmake_utils/qmake_utils.pri)

INCLUDEPATH += ./ \
    $${PWD}/../libs/log4qt \
    $${PWD}/../libs/tiny_aes

SOURCES += \
    algo/easy_result_algo.cpp \
    algo/moderate_result_algo.cpp \
    algo/strict_result_algo.cpp \
    algo/thema_add_operation.cpp \
    algo/thema_delete_operation.cpp \
    algo/thema_replace_operation.cpp \
    file_downloader.cpp \
    image_provider.cpp \
    manager.cpp \
    pages/help_page.cpp \
    pages/home_page.cpp \
    pages/page.cpp \
    pages/settings_page.cpp \
    pages/stats_page.cpp \
    pages/thema_page.cpp \
    pages/words_page.cpp \
    settings.cpp \
    thema_updater.cpp \
    main.cpp \
    message_bar.cpp \
    app_updater.cpp \
    pages/about_page.cpp

HEADERS += \
    algo/easy_result_algo.h \
    algo/moderate_result_algo.h \
    algo/result_algo.h \
    algo/strict_result_algo.h \
    algo/thema_add_operation.h \
    algo/thema_delete_operation.h \
    algo/thema_file_operation.h \
    algo/thema_replace_operation.h \
    file_downloader.h \
    image_provider.h \
    pages/help_page.h \
    pages/home_page.h \
    pages/page.h \
    pages/page_i.h \
    pages/settings_page.h \
    pages/stats_page.h \
    pages/thema_page.h \
    pages/words_page.h \
    settings.h \
    thema_updater.h \
    manager.h \
    message_bar.h \
    app_updater.h \
    pages/about_page.h

RESOURCES += \
    resources.qrc

win32{
  RC_FILE = der_artikel.rc
}

# Lupdate cosiders files added under SOURCES variable only.
hack_for_qml_lupdate {
    SOURCES += qml/der_artikel/*.qml
}

TRANSLATIONS += ./der_artikel_de.ts \
    ./der_artikel_en.ts \
    ./der_artikel_hin.ts

OTHER_FILES += ./der_artikel_de.ts \
    ./der_artikel_en.ts \
    ./der_artikel_hin.ts \
    code_comment_template.txt \
    qml/der_artikel/utils.js

# Add more folders to ship with the application, here
folder_01.source = languages
folder_01.target =
DEPLOYMENTFOLDERS += folder_01
doDeployment()

mac {
    LIBS += -L$${DESTDIR}/$${TARGET}.app/Contents/MacOS -llog4qt
    LIBS += -L$${DESTDIR}/$${TARGET}.app/Contents/MacOS -laes
} else {
    LIBS += -L$${DESTDIR} -llog4qt
    LIBS += -L$${DESTDIR} -laes
}


# Copy log4qt files to build dir
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



#******************************************************************************
#   Android settings
#*****************************************************************************/
android {
    # libs dependencies
    ANDROID_DEPLOYMENT_DEPENDENCIES = \
        jar/QtAndroid-bundled.jar \
        jar/QtAndroidAccessibility-bundled.jar \
        jar/QtMultimedia-bundled.jar \
        lib/libQt5Core.so \
        lib/libQt5Gui.so \
        lib/libQt5Network.so \
        lib/libQt5Qml.so \
        lib/libQt5Quick.so \
        lib/libQt5QuickParticles.so \
        lib/libQt5Multimedia.so \
        lib/libQt5MultimediaQuick_p.so \
        lib/libQt5Xml.so \
        plugins/bearer/libqgenericbearer.so \
        plugins/platforms/android/libqtforandroid.so \
        plugins/platforms/libqeglfs.so \
        plugins/audio/libqtaudio_opensles.so \
        qml/QtQml/Models.2/libmodelsplugin.so \
        qml/QtQuick/Window.2/libwindowplugin.so \
        qml/QtQuick.2/libqtquick2plugin.so \
        qml/QtMultimedia/libdeclarative_multimedia.so

    # Assets dependencies
    ANDROID_DEPLOYMENT_DEPENDENCIES += \
        qml/QtGraphicalEffects/Blend.qml \
        qml/QtGraphicalEffects/BrightnessContrast.qml \
        qml/QtGraphicalEffects/Colorize.qml \
        qml/QtGraphicalEffects/ColorOverlay.qml \
        qml/QtGraphicalEffects/ConicalGradient.qml \
        qml/QtGraphicalEffects/Desaturate.qml \
        qml/QtGraphicalEffects/DirectionalBlur.qml \
        qml/QtGraphicalEffects/Displace.qml \
        qml/QtGraphicalEffects/DropShadow.qml \
        qml/QtGraphicalEffects/FastBlur.qml \
        qml/QtGraphicalEffects/GammaAdjust.qml \
        qml/QtGraphicalEffects/GaussianBlur.qml \
        qml/QtGraphicalEffects/Glow.qml \
        qml/QtGraphicalEffects/HueSaturation.qml \
        qml/QtGraphicalEffects/InnerShadow.qml \
        qml/QtGraphicalEffects/LevelAdjust.qml \
        qml/QtGraphicalEffects/LinearGradient.qml \
        qml/QtGraphicalEffects/MaskedBlur.qml \
        qml/QtGraphicalEffects/OpacityMask.qml \
        qml/QtGraphicalEffects/private/FastGlow.qml \
        qml/QtGraphicalEffects/private/FastInnerShadow.qml \
        qml/QtGraphicalEffects/private/FastMaskedBlur.qml \
        qml/QtGraphicalEffects/private/GaussianDirectionalBlur.qml \
        qml/QtGraphicalEffects/private/GaussianGlow.qml \
        qml/QtGraphicalEffects/private/GaussianInnerShadow.qml \
        qml/QtGraphicalEffects/private/GaussianMaskedBlur.qml \
        qml/QtGraphicalEffects/private/SourceProxy.qml \
        qml/QtGraphicalEffects/qmldir \
        qml/QtGraphicalEffects/RadialBlur.qml \
        qml/QtGraphicalEffects/RadialGradient.qml \
        qml/QtGraphicalEffects/RectangularGlow.qml \
        qml/QtGraphicalEffects/RecursiveBlur.qml \
        qml/QtGraphicalEffects/ThresholdMask.qml \
        qml/QtGraphicalEffects/ZoomBlur.qml \
        qml/QtMultimedia/plugins.qmltypes \
        qml/QtMultimedia/qmldir \
        qml/QtMultimedia/Video.qml \
        qml/QtQml/Models.2/qmldir \
        qml/QtQuick/Window.2/plugins.qmltypes \
        qml/QtQuick/Window.2/qmldir \
        qml/QtQuick.2/plugins.qmltypes \
        qml/QtQuick.2/qmldir

    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
    OTHER_FILES += \
        android/AndroidManifest.xml \
        android/res/values/libs.xml
}

