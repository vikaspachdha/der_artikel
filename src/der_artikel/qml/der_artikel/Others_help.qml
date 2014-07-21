import QtQuick 2.1

Flickable {
    anchors.fill: parent
    anchors.margins: 4
    Text {
        id: content_text
        anchors.fill: parent
        text:qsTr("For any other assistance or help please mail your queries to \nmail@derartikel.com \
\n\nVisit www.derartikel.com for developer's contact details.") + settings.i18n_empty_string

        wrapMode: Text.WordWrap
        font.family: regular_font.name
        color:color_palette.color_font_01
        font.pixelSize: normalTextSize
    }
    contentHeight: content_text.contentHeight
}
