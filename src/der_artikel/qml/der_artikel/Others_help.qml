import QtQuick 2.0

Flickable {
    anchors.fill: parent
    anchors.margins: 4
    Text {
        id: content_text
        anchors.fill: parent
        text:"For any other assistance or help please mail your queries to \nmail@vikaspachdha.com \
\n\nVisit vikaspachdha.com for alternate contact"

        wrapMode: Text.WordWrap
        font.family: custom_regular.name
        color:cp_blue.colorf01
        font.pixelSize: 16
    }
    contentHeight: content_text.contentHeight
}
