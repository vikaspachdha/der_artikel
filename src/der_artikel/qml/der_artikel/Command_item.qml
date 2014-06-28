import QtQuick 2.1

Item {
    id: root_item
    width: 52
    height: 52
    property alias cmd_text:item_label.text
    property string icon_name:"command"

    signal commandActivated

    Image {
        id: icon
        height: width
        width:32
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        source: mouse_area.pressed ? "qrc:/res/resources/" + icon_name +"_active.png" : root_item.enabled ? "qrc:/res/resources/" + icon_name +".png" : "qrc:/res/resources/" + icon_name +"_disabled.png"
    }

    Item {
        id: lableParent
        anchors.top: icon.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        Text {
            id: item_label
            anchors.baseline: parent.verticalCenter
            anchors.baselineOffset: 4
            anchors.right: parent.right
            anchors.left: parent.left
            color:color_palette.color_font_01
            font.family: regular_font.name
            font.pixelSize: commandTextSize
            horizontalAlignment: Text.AlignHCenter
        }
    }



    MouseArea {
        id: mouse_area
        anchors.fill: parent
        onClicked: {
            root_item.commandActivated()
            clickSnd.play()
        }
    }
}
