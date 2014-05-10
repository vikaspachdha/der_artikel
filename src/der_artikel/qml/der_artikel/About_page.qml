import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0

Page {
    page_id:Manager.ABOUT_PAGE
    Rectangle {
        id: background
        anchors.fill: parent
        color:color_palette.color_bg_01
        radius: 4
    }
    Flickable {
        anchors.fill: background
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
                font.pixelSize: 18
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                id: content_text
                anchors.top: version_text.bottom
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.right: parent.right
                text:"The program is provided AS IS with NO \
WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND \
FITNESS FOR A PARTICULAR PURPOSE."

                wrapMode: Text.WordWrap
                font.family: regular_font.name
                color:color_palette.color_font_01
                font.pixelSize: 14
            }

            Text {
                id: developer_text
                anchors.top: content_text.bottom
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.right: parent.right
                text:"<u>Developers:</u><br><br> \
Vikas Pachdha (www.vikaspachdha.com)<br><br>Mohita Gandotra (mohitagandotra@gmail.com)<br><br><br> \
<u>Thema contributors:</u><br><br> \
Vikas Pachdha<br><br> \
Mohita Gandotra"

                wrapMode: Text.WordWrap
                textFormat: Text.StyledText
                font.family: regular_font.name
                color:color_palette.color_font_01
                font.pixelSize: 14
                horizontalAlignment: Text.AlignHCenter
            }
        }

        contentHeight: text_rect.childrenRect.height
    }
}
