
QT_LIB_PATH=/Users/vikas/qt/qt520/5.2.0/clang_64/lib
SOURCE_PATH=./source
OUTPUT_PATH=./output
TEMPLATE_PATH=./template
APP_NAME=der_artikel

APP_PATH=$OUTPUT_PATH/$APP_NAME.app/Contents/MacOS


#remove old
rm -rf $OUTPUT_PATH/$APP_NAME.app


#copy Template
cp -R $TEMPLATE_PATH/$APP_NAME.app $OUTPUT_PATH


#copy source
cp $SOURCE_PATH/$APP_NAME.app/Contents/MacOS/$APP_NAME $APP_PATH
cp $SOURCE_PATH/$APP_NAME.app/Contents/Resources/languages/*.qm $OUTPUT_PATH/$APP_NAME.app/Contents/Resources/languages
cp $SOURCE_PATH/$APP_NAME.app/Contents/Resources/thema/*.AKL $OUTPUT_PATH/$APP_NAME.app/Contents/Resources/thema


# copy Frameworks
cp -R $QT_LIB_PATH/QtQuick.framework $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtQml.framework $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtNetwork.framework $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtCore.framework $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtGui.framework $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtWidgets.framework $APP_PATH/../Frameworks
cp -R $QT_LIB_PATH/QtXml.framework $APP_PATH/../Frameworks


# copy Libs
cp /usr/lib/libstdc++.6.dylib $APP_PATH/../Libs
cp /usr/lib/libSystem.B.dylib $APP_PATH/../Libs



# Dependency fix - Frameworks Internal
install_name_tool ./output/der_artikel.app/Contents/Frameworks/QtGui.framework/Versions/5/QtGui -change $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore


# Dependency fix - Frameworks 
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtQuick.framework/Versions/5/QtQuick @executable_path/../Frameworks/QtQuick.framework/Versions/5/QtQuick
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtQml.framework/Versions/5/QtQml @executable_path/../Frameworks/QtQml.framework/Versions/5/QtQml
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtNetwork.framework/Versions/5/QtNetwork @executable_path/../Frameworks/QtNetwork.framework/Versions/5/QtNetwork
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets.framework/Versions/5/QtWidgets
install_name_tool $APP_PATH/$APP_NAME -change $QT_LIB_PATH/QtXml.framework/Versions/5/QtXml @executable_path/../Frameworks/QtXml.framework/Versions/5/QtXml


# Libs
install_name_tool $APP_PATH/$APP_NAME -change /usr/lib/libstdc++.6.dylib @executable_path/../Libs/libstdc++.6.dylib
install_name_tool $APP_PATH/der_artikel -change /usr/lib/libSystem.B.dylib @executable_path/../Libs/libSystem.B.dylib
