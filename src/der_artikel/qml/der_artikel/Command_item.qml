import QtQuick 2.0

Item {
    id: root_item
    width: childrenRect.width
    height: childrenRect.height
    property alias cmd_text:item_label.text
    property alias cmd_icon:icon.source

    signal commandActivated

    Image {
        id: icon
        height: width
        width:sourceSize.width
        anchors.left: parent.left
        anchors.top: parent.top
        source: "qrc:/res/resources/default_thema.png"
    }

    Text {
        id: item_label
        text: qsTr("Unkown CMD")
        anchors.top: icon.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        font.pointSize: 12
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
