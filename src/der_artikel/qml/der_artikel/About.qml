import QtQuick 2.1

Flickable {
    anchors.fill: parent
    anchors.margins: 4
    Item {
        id:text_rect
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height:childrenRect.height
        Text {
            id: version_text
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 8
            text:qsTr("Version\n") + manager.version_string + settings.i18n_empty_string

            wrapMode: Text.WordWrap
            font.family: regular_font.name
            color:color_palette.color_font_01
            font.pixelSize: normalTextSize
            font.italic: true
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            id: content_text
            anchors.top: version_text.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.right: parent.right
            text:"The SOFTWARE and the data used in the software and any related documentation \
is provided \"as is\" without warranty of any kind, either express or implied, including, without \
limitation, the implied warranties or merchantability or fitness for a particular purpose. The \
entire risk arising out of use or performance of the SOFTWARE remains with you."

            wrapMode: Text.WordWrap
            font.family: regular_font.name
            color:color_palette.color_font_01
            font.pixelSize: normalTextSize
        }

        Text {
            id: developer_text
            anchors.top: content_text.bottom
            anchors.topMargin: 30
            anchors.left: parent.left
            anchors.right: parent.right
            text:"
<u>Developers:</u> \
<p><ul><li>Vikas Pachdha (www.vikaspachdha.com)</li><li>Mohita Gandotra (mohitagandotra@gmail.com)</li></ul></p>

<u>Thema contributors:</u>\
<p><ul><li>Vikas Pachdha</li><li>Mohita Gandotra</li></ul></p>"

            wrapMode: Text.WordWrap
            textFormat: Text.StyledText
            font.family: regular_font.name
            color:color_palette.color_font_01
            font.pixelSize: normalTextSize
        }
    }

    contentHeight: text_rect.childrenRect.height
}
