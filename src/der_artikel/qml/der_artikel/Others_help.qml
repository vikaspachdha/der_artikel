import QtQuick 2.1

Flickable {
    anchors.fill: parent
    anchors.margins: 4
    Text {
        id: content_text
        anchors.fill: parent
        text:"For any other assistance or help please mail your queries to \nmail@vikaspachdha.com \
\n\nVisit vikaspachdha.com for alternate contact"

        wrapMode: Text.WordWrap
        font.family: regular_font.name
        color:color_palette.color_font_01
        font.pixelSize: normalTextSize
    }
    contentHeight: content_text.contentHeight
}
