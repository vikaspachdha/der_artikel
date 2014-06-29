
QT_LIB_PATH=/Users/vikas/qt/qt531/5.3/clang_64/lib
SOURCE_PATH=./source
OUTPUT_PATH=./output
TEMPLATE_PATH=./template
APP_NAME=der_artikel

APP_PATH=$OUTPUT_PATH/$APP_NAME.app/Contents/MacOS


###remove old
rm -rf $OUTPUT_PATH/$APP_NAME.app



###################################################################################
# Copy Dependencies & App
###################################################################################

###copy Template
cp -R $TEMPLATE_PATH/$APP_NAME.app $OUTPUT_PATH


###copy source
cp $SOURCE_PATH/$APP_NAME.app/Contents/MacOS/$APP_NAME $APP_PATH
cp $SOURCE_PATH/$APP_NAME.app/Contents/Resources/languages/*.qm $OUTPUT_PATH/$APP_NAME.app/Contents/Resources/languages
cp $SOURCE_PATH/$APP_NAME.app/Contents/Resources/thema/*.AKL $OUTPUT_PATH/$APP_NAME.app/Contents/Resources/thema


### copy Frameworks
cp -R $QT_LIB_PATH/QtQuick.framework/Versions/5/QtQuick $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtQml.framework/Versions/5/QtQml $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtNetwork.framework/Versions/5/QtNetwork $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtGui.framework/Versions/5/QtGui $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtWidgets.framework/Versions/5/QtWidgets $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtXml.framework/Versions/5/QtXml $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtMultimedia.framework/Versions/5/QtMultimedia $APP_PATH/../Frameworks


### copy Libs
cp /usr/lib/libstdc++.6.dylib $APP_PATH/../Libs
cp /usr/lib/libSystem.B.dylib $APP_PATH/../Libs
cp $SOURCE_PATH/$APP_NAME.app/Contents/MacOS/*.dylib $APP_PATH/../Libs






###################################################################################
# Dependency fix
###################################################################################


### Dependency fix - Frameworks Internal
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtGui -change $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore


### Dependency fix - Frameworks 
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtQuick.framework/Versions/5/QtQuick @executable_path/../Frameworks/QtQuick
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtQml.framework/Versions/5/QtQml @executable_path/../Frameworks/QtQml
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtNetwork.framework/Versions/5/QtNetwork @executable_path/../Frameworks/QtNetwork
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtXml.framework/Versions/5/QtXml @executable_path/../Frameworks/QtXml
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtMultimedia.framework/Versions/5/QtMultimedia @executable_path/../Frameworks/QtMultimedia

### Libs
install_name_tool $APP_PATH/$APP_NAME -change /usr/lib/libstdc++.6.dylib @executable_path/../Libs/libstdc++.6.dylib
install_name_tool $APP_PATH/der_artikel -change /usr/lib/libSystem.B.dylib @executable_path/../Libs/libSystem.B.dylib
install_name_tool $APP_PATH/der_artikel -change liblog4qt.1.dylib @executable_path/../Libs/liblog4qt.1.dylib
