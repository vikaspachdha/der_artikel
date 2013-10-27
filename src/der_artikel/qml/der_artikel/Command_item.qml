import QtQuick 2.0

Item {
    id: root_item
    width: 32
    height: 42
    property alias cmd_text:item_label.text
    property alias cmd_icon:icon.source

    signal commandActivated

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
        text: qsTr("Unkown CMD")
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
            root_item.commandActivated()
        }
    }
}
