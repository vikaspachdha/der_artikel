import QtQuick 2.0

Item {
    id:lbl_root

    property alias lblText:label.text
    property alias textPxSize:label.font.pixelSize
    property alias text_anchors: label.anchors
    property alias under_line:label.font.underline

    width: label.width+12
    height: label.height+8
    Text {
        id: label
        x:2
        anchors.verticalCenter: parent.verticalCenter
        font.family: command_font.name
        text: qsTr("Label")
        color:cp_blue.colorf01
        font.pixelSize: 18
    }
}
