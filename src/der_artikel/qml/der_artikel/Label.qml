import QtQuick 2.1

Item {
    id:lbl_root

    property alias lblText:label.text
    property alias textPxSize:label.font.pixelSize
    property alias text_anchors: label.anchors
    property alias under_line:label.font.underline
    property alias background_color: background.color
    property alias text_color: label.color
    width: label.width+12
    height: label.height+8

    Rectangle {
        id: background
        anchors.fill:parent
        radius: 4
        color:"transparent"
    }

    Text {
        id: label
        x:2
        anchors.verticalCenter: parent.verticalCenter
        font.family: command_font.name
        color:color_palette.color_font_01
        font.pixelSize: 18
    }
}
