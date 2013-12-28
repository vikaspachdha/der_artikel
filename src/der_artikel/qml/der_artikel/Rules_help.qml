import QtQuick 2.0

Flickable {
    anchors.fill: parent
    anchors.margins: 4
    Text {
        id: content_text
        anchors.fill: parent
        text:"Rules"

        wrapMode: Text.WordWrap
        font.family: custom_regular.name
        color:cp_blue.colorf02
        font.pixelSize: 16
    }
    contentHeight: content_text.contentHeight
}
