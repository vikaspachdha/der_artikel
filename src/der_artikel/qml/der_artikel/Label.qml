import QtQuick 2.1

Item {
    id:lbl_root

    property alias lblText:label.text
    property alias textPxSize:label.font.pixelSize
    property alias text_h_alignment: label.horizontalAlignment
    property alias under_line:label.font.underline
    property alias background_color: background.color
    property alias text_color: label.color
    width: 80
    height: 30

    Rectangle {
        id: background
        anchors.fill:parent
        radius: 4
        color:"transparent"
    }

    Text {
        id: label
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 2
        anchors.rightMargin: 2
        anchors.baseline: parent.verticalCenter
        anchors.baselineOffset: (font.pixelSize/2) - 2
        horizontalAlignment: Text.AlignHCenter
        font.family: regular_font.name
        color:color_palette.color_font_01
        font.pixelSize: normalTextSize
    }
}
