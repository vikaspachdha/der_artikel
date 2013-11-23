import QtQuick 2.0

Rectangle {
    id:lbl_root

    property alias lblText:label.text
    property alias textPxSize:label.font.pixelSize
    property alias text_anchors: label.anchors

    width: label.width+12
    height: label.height+8
    radius: 0
    color:"#8d8b8b"

    Text {
        id: label
        x:2
        anchors.verticalCenter: parent.verticalCenter
        text: qsTr("Label")
        font.pixelSize: 14
    }
}
