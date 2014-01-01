import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Flickable {
    anchors.fill: parent
    anchors.margins: 4

    contentHeight: languages_btn_col.height

    Column {
        id: languages_btn_col
        anchors.top: parent.top
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        spacing: 4

        Button {
            id:english_btn
            width:parent.width
            text_anchors.horizontalCenter: english_btn.horizontalCenter
            isDown: settings.language === Settings.ENGLISH
            buttonText: "English"
            onActivated: settings.language = Settings.ENGLISH
        }

        Button {
            id:german_btn
            width:parent.width
            text_anchors.horizontalCenter: german_btn.horizontalCenter
            isDown: settings.language === Settings.GERMAN
            buttonText: "Deutsch"
            onActivated: settings.language = Settings.GERMAN
        }

        Button {
            id:hindi_btn
            width:parent.width
            text_anchors.horizontalCenter: hindi_btn.horizontalCenter
            isDown: settings.language === Settings.HINDI
            buttonText: "हिंदी"
            onActivated: settings.language = Settings.HINDI
        }
    }
}
