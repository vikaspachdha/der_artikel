import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Page {
    page_id:Manager.ABOUT_PAGE
    Rectangle {
        id: background
        anchors.fill: parent
        color:cp_blue.colorBtn02
        radius: 4
    }
    Flickable {
        anchors.fill: background
        anchors.margins: 4
        Text {
            id: version_text
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height:60
            anchors.topMargin: 8
            text:qsTr("Version\n") + manager.version_string

            wrapMode: Text.WordWrap
            font.family: custom_regular.name
            color:cp_blue.colorf02
            font.pixelSize: 18
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            id: content_text
            anchors.top: version_text.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            text:"The program is provided AS IS with NO \
WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND \
FITNESS FOR A PARTICULAR PURPOSE."

            wrapMode: Text.WordWrap
            font.family: custom_regular.name
            color:cp_blue.colorf02
            font.pixelSize: 16
        }

        contentHeight: content_text.height + version_text.height
    }
}
