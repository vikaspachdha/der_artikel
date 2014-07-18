QT_PATH=/Users/vikas/qt/qt531/5.3/clang_64
QT_LIB_PATH=$QT_PATH/lib
QT_PLUGINS_PATH=$QT_PATH/Plugins
QT_QML_PLUGINS_PATH=$QT_PATH/qml
SOURCE_PATH=./source
OUTPUT_PATH=./output
TEMPLATE_PATH=./template
APP_NAME=der_artikel

APP_PATH=$OUTPUT_PATH/$APP_NAME.app/Contents/MacOS


###################################################################################
# Remove old App files
###################################################################################
echo Removing old files...
###remove old
rm -rf $OUTPUT_PATH/$APP_NAME.app




###################################################################################
# Copy Dependencies & App
###################################################################################
echo Copying template files...
###copy Template
cp -R $TEMPLATE_PATH/$APP_NAME.app $OUTPUT_PATH

echo Copying compiled files...
###copy source
cp $SOURCE_PATH/$APP_NAME.app/Contents/MacOS/$APP_NAME $APP_PATH
cp $SOURCE_PATH/$APP_NAME.app/Contents/Resources/languages/*.qm $OUTPUT_PATH/$APP_NAME.app/Contents/Resources/languages
cp $SOURCE_PATH/$APP_NAME.app/Contents/Resources/thema/*.AKL $OUTPUT_PATH/$APP_NAME.app/Contents/Resources/thema

echo Copying qt frameworks...
### copy Frameworks
cp -R $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtGui.framework/Versions/5/QtGui $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtMultimedia.framework/Versions/5/QtMultimedia $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtMultimediaQuick_p.framework/Versions/5/QtMultimediaQuick_p $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtNetwork.framework/Versions/5/QtNetwork $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtPrintSupport.framework/Versions/5/QtPrintSupport $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtQml.framework/Versions/5/QtQml $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtQuick.framework/Versions/5/QtQuick $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtWidgets.framework/Versions/5/QtWidgets $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtXml.framework/Versions/5/QtXml $APP_PATH/../Frameworks

#echo Copying qt plugins...
### copy Plugins - uncomment to copy from qt installation. As of now required plugins are added to template.
#cp -R $QT_PLUGINS_PATH/platforms $APP_PATH

#echo Copying qml plugins...
### copy QML Plugins
#cp -R $QT_QML_PLUGINS_PATH/QtGraphicalEffects $APP_PATH
#cp -R $QT_QML_PLUGINS_PATH/QtMultimedia $APP_PATH
#cp -R $QT_QML_PLUGINS_PATH/QtQuick $APP_PATH
#cp -R $QT_QML_PLUGINS_PATH/QtQuick.2 $APP_PATH

echo Copying libs...
### copy Libs
cp $SOURCE_PATH/$APP_NAME.app/Contents/MacOS/libaes.1.dylib $APP_PATH/../Libs
cp $SOURCE_PATH/$APP_NAME.app/Contents/MacOS/liblog4qt.1.dylib $APP_PATH/../Libs




###################################################################################
# ID's for frameworks.
###################################################################################
echo Fixing id of frameworks...
install_name_tool -id @executable_path/../Frameworks/QtCore ./output/der_artikel.app/Contents/Frameworks/QtCore
install_name_tool -id @executable_path/../Frameworks/QtGui ./output/der_artikel.app/Contents/Frameworks/QtGui
install_name_tool -id @executable_path/../Frameworks/QtMultimedia ./output/der_artikel.app/Contents/Frameworks/QtMultimedia
install_name_tool -id @executable_path/../Frameworks/QtMultimediaQuick_p ./output/der_artikel.app/Contents/Frameworks/QtMultimediaQuick_p
install_name_tool -id @executable_path/../Frameworks/QtNetwork ./output/der_artikel.app/Contents/Frameworks/QtNetwork
install_name_tool -id @executable_path/../Frameworks/QtPrintSupport ./output/der_artikel.app/Contents/Frameworks/QtPrintSupport
install_name_tool -id @executable_path/../Frameworks/QtQml ./output/der_artikel.app/Contents/Frameworks/QtQml
install_name_tool -id @executable_path/../Frameworks/QtQuick ./output/der_artikel.app/Contents/Frameworks/QtQuick
install_name_tool -id @executable_path/../Frameworks/QtWidgets ./output/der_artikel.app/Contents/Frameworks/QtWidgets
install_name_tool -id @executable_path/../Frameworks/QtXml ./output/der_artikel.app/Contents/Frameworks/QtXml




###################################################################################
# Dependency fix
###################################################################################

echo Fixing qt framwork internal dependencies...
### Dependency fix - Frameworks Internal
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtGui -change $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtMultimedia -change $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtMultimedia -change $QT_LIB_PATH/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtMultimedia -change $QT_LIB_PATH/QtNetwork.framework/Versions/5/QtNetwork @executable_path/../Frameworks/QtNetwork
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtMultimediaQuick_p -change $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtMultimediaQuick_p -change $QT_LIB_PATH/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtMultimediaQuick_p -change $QT_LIB_PATH/QtMultimedia.framework/Versions/5/QtMultimedia @executable_path/../Frameworks/QtMultimedia
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtMultimediaQuick_p -change $QT_LIB_PATH/QtNetwork.framework/Versions/5/QtNetwork @executable_path/../Frameworks/QtNetwork
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtMultimediaQuick_p -change $QT_LIB_PATH/QtQml.framework/Versions/5/QtQml @executable_path/../Frameworks/QtQml
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtMultimediaQuick_p -change $QT_LIB_PATH/QtQuick.framework/Versions/5/QtQuick @executable_path/../Frameworks/QtQuick
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtNetwork -change $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtPrintSupport -change $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtPrintSupport -change $QT_LIB_PATH/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtPrintSupport -change $QT_LIB_PATH/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtQml -change $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtQml -change $QT_LIB_PATH/QtNetwork.framework/Versions/5/QtNetwork @executable_path/../Frameworks/QtNetwork
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtQuick -change $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtQuick -change $QT_LIB_PATH/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtQuick -change $QT_LIB_PATH/QtNetwork.framework/Versions/5/QtNetwork @executable_path/../Frameworks/QtNetwork
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtQuick -change $QT_LIB_PATH/QtQml.framework/Versions/5/QtQml @executable_path/../Frameworks/QtQml
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtWidgets -change $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtWidgets -change $QT_LIB_PATH/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtXml -change $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore

echo Fixing qt plugins dependencies...
### Dependency fix - Plugins -> Frameworks
install_name_tool $APP_PATH/QtMultimedia/libdeclarative_multimedia.dylib -change $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore
install_name_tool $APP_PATH/QtMultimedia/libdeclarative_multimedia.dylib -change $QT_LIB_PATH/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui
install_name_tool $APP_PATH/QtMultimedia/libdeclarative_multimedia.dylib -change $QT_LIB_PATH/QtMultimedia.framework/Versions/5/QtMultimedia @executable_path/../Frameworks/QtMultimedia
install_name_tool $APP_PATH/QtMultimedia/libdeclarative_multimedia.dylib -change $QT_LIB_PATH/QtMultimediaQuick_p.framework/Versions/5/QtMultimediaQuick_p @executable_path/../Frameworks/QtMultimediaQuick_p
install_name_tool $APP_PATH/QtMultimedia/libdeclarative_multimedia.dylib -change $QT_LIB_PATH/QtNetwork.framework/Versions/5/QtNetwork @executable_path/../Frameworks/QtNetwork
install_name_tool $APP_PATH/QtMultimedia/libdeclarative_multimedia.dylib -change $QT_LIB_PATH/QtQml.framework/Versions/5/QtQml @executable_path/../Frameworks/QtQml
install_name_tool $APP_PATH/QtMultimedia/libdeclarative_multimedia.dylib -change $QT_LIB_PATH/QtQuick.framework/Versions/5/QtQuick @executable_path/../Frameworks/QtQuick
install_name_tool $APP_PATH/QtQuick.2/libqtquick2plugin.dylib -change $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore
install_name_tool $APP_PATH/QtQuick.2/libqtquick2plugin.dylib -change $QT_LIB_PATH/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui
install_name_tool $APP_PATH/QtQuick.2/libqtquick2plugin.dylib -change $QT_LIB_PATH/QtNetwork.framework/Versions/5/QtNetwork @executable_path/../Frameworks/QtNetwork
install_name_tool $APP_PATH/QtQuick.2/libqtquick2plugin.dylib -change $QT_LIB_PATH/QtQml.framework/Versions/5/QtQml @executable_path/../Frameworks/QtQml
install_name_tool $APP_PATH/QtQuick.2/libqtquick2plugin.dylib -change $QT_LIB_PATH/QtQuick.framework/Versions/5/QtQuick @executable_path/../Frameworks/QtQuick
install_name_tool $APP_PATH/QtQuick/Window.2/libwindowplugin.dylib -change $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore
install_name_tool $APP_PATH/QtQuick/Window.2/libwindowplugin.dylib -change $QT_LIB_PATH/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui
install_name_tool $APP_PATH/QtQuick/Window.2/libwindowplugin.dylib -change $QT_LIB_PATH/QtNetwork.framework/Versions/5/QtNetwork @executable_path/../Frameworks/QtNetwork
install_name_tool $APP_PATH/QtQuick/Window.2/libwindowplugin.dylib -change $QT_LIB_PATH/QtQml.framework/Versions/5/QtQml @executable_path/../Frameworks/QtQml
install_name_tool $APP_PATH/QtQuick/Window.2/libwindowplugin.dylib -change $QT_LIB_PATH/QtQuick.framework/Versions/5/QtQuick @executable_path/../Frameworks/QtQuick
install_name_tool $APP_PATH/platforms/libqcocoa.dylib -change $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore
install_name_tool $APP_PATH/platforms/libqcocoa.dylib -change $QT_LIB_PATH/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui
install_name_tool $APP_PATH/platforms/libqcocoa.dylib -change $QT_LIB_PATH/QtPrintSupport.framework/Versions/5/QtPrintSupport @executable_path/../Frameworks/QtPrintSupport
install_name_tool $APP_PATH/platforms/libqcocoa.dylib -change $QT_LIB_PATH/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets

echo Fixing libs dependencies...
### Dependency fix - Plugins -> Frameworks
install_name_tool ./output/der_artikel.app/Contents/Libs/liblog4qt.1.dylib -change $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore
install_name_tool ./output/der_artikel.app/Contents/Libs/libaes.1.dylib -change $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore

echo Fixing app dependencies...
### Dependency fix - app -> Frameworks 
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtMultimedia.framework/Versions/5/QtMultimedia @executable_path/../Frameworks/QtMultimedia
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtNetwork.framework/Versions/5/QtNetwork @executable_path/../Frameworks/QtNetwork
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtQml.framework/Versions/5/QtQml @executable_path/../Frameworks/QtQml
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtQuick.framework/Versions/5/QtQuick @executable_path/../Frameworks/QtQuick
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtXml.framework/Versions/5/QtXml @executable_path/../Frameworks/QtXml

### Dependency fix - app -> Libs
install_name_tool $APP_PATH/$APP_NAME -change libaes.1.dylib @executable_path/../Libs/libaes.1.dylib
install_name_tool $APP_PATH/$APP_NAME -change liblog4qt.1.dylib @executable_path/../Libs/liblog4qt.1.dylib

echo Finished.


