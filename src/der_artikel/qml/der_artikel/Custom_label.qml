import QtQuick 2.1

Rectangle {

    property alias text:label_text.text
    property alias font_size:label_text.font.pixelSize
    property alias font_color:label_text.color
    property alias text_horizontal_alignment: label_text.horizontalAlignment

    height: 30
    color: "#fff"
    Text {
        id: label_text
        font.pixelSize: normalTextSize
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.baseline: parent.verticalCenter
        anchors.baselineOffset: 4
        horizontalAlignment: Text.AlignHCenter
        font.family: regular_font.name
    }
}
