import QtQuick 2.0

Item {
    id: root_item
    width: childrenRect.width
    height: childrenRect.height
    property alias cmd_text:item_label.text
    property string icon_name:"command"

    signal commandActivated

    Image {
        id: icon
        height: width
        width:sourceSize.width
        anchors.left: parent.left
        anchors.top: parent.top
        source: mouse_area.pressed ? "qrc:/res/resources/" + icon_name +"_activ.png" : root_item.enabled ? "qrc:/res/resources/" + icon_name +".png" : "qrc:/res/resources/" + icon_name +"_disabled.png"
    }

    Text {
        id: item_label
        text: qsTr("Unkown CMD")
        anchors.top: icon.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        color:cp_blue.colorf01
        font.family: command_font.name
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
        smooth:true
    }

    MouseArea {
        id: mouse_area
        anchors.fill: parent
        onClicked: {
            root_item.commandActivated()
        }
    }
}
