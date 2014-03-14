import QtQuick 2.0

Flickable {
    anchors.fill: parent
    anchors.margins: 4

    contentHeight: cp_btn_col.height

    Column {
        id: cp_btn_col
        anchors.top: parent.top
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        spacing: 4

        Button {
            id:cp_blue_btn
            width:parent.width
            text_anchors.horizontalCenter: cp_blue_btn.horizontalCenter
            isDown: color_palette === cp_blue
            buttonText: qsTr("Deep blue") + settings.i18n_empty_string
            onActivated: color_palette = cp_blue
        }

        Button {
            id:cp_orange_btn
            width:parent.width
            text_anchors.horizontalCenter: cp_orange_btn.horizontalCenter
            isDown: color_palette === cp_orange
            buttonText: qsTr("Tangy Orange") + settings.i18n_empty_string
            onActivated: color_palette = cp_orange
        }

        Button {
            id:cp_night_btn
            width:parent.width
            text_anchors.horizontalCenter: cp_night_btn.horizontalCenter
            isDown: color_palette === cp_night
            buttonText: qsTr("Dark night") + settings.i18n_empty_string
            onActivated: color_palette = cp_night
        }

    }
}
