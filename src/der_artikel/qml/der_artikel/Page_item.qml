import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0
Item {
    id: root_item
    width: 80
    height: 80
    property alias label_text:item_label.text
    property alias page_icon:icon.source
    Rectangle {
        anchors.fill:icon
        color:color_palette.color_btn_01
        radius:8
    }

    Image {
        id: icon
        width:64
        height: width
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
        source: "qrc:/res/resources/default_thema.png"
    }

    Text {
        id: item_label
        anchors.top: icon.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 0
        horizontalAlignment: Text.AlignHCenter
        smooth:true
        color:color_palette.color_font_01
        font.family: command_font.name
        font.pixelSize: 18
    }

    MouseArea {
        id: mouse_area
        anchors.fill: parent
        onClicked: {
            manager.current_page=model.src_page_id
        }
    }
}
