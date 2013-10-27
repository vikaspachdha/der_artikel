import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0
Item {
    id: root_item
    width: 64
    height: 74
    property alias label_text:item_label.text
    property alias page_icon:icon.source
    property int page_id: Manager.INVALID
    Image {
        id: icon
        height: width
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        source: "qrc:/res/resources/default_thema.png"
    }

    Text {
        id: item_label
        text: qsTr("Unkown Page")
        anchors.top: icon.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 0
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
        smooth:true
    }

    MouseArea {
        id: mouse_area
        anchors.fill: parent
        onClicked: {
            manager.current_page=page_id
        }
    }
}
