import QtQuick 2.0
import QtQuick.Controls 1.0

Rectangle {
    id: msg_bar
    color:"blue"
    property alias title:msg_title.text
    property alias message:msg_text.text

    Rectangle {
        id: icon
        height: width
        color:"red"
        anchors {
            left: msg_bar.left
            top: msg_bar.top
            bottom: msg_bar.bottom
        }
    }

    Text {
        id: msg_title
        height: msg_bar.height * 0.40
        anchors {
            left: icon.left
            top: msg_bar.top
            right: msg_bar.right
        }
        font.pointSize: height
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment:  Text.AlignVCenter
        text:"Title"
    }

    Text {
        id: msg_text
        height: msg_bar.height * 0.40
        anchors {
            left: icon.left
            top: msg_title.bottom
            right: msg_bar.right
            bottom: msg_bar.bottom
        }
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment:  Text.AlignVCenter
        font.pointSize: height/3
        text:"message"
    }

    Button {
        text:"test Button"
        onClicked: {
            if(msg_bar.y == rootItem.y) {
                msg_bar.y = rootItem.height - msg_bar.height
            } else {
               msg_bar.y = rootItem.y
            }
        }
    }
    Behavior on y {
            NumberAnimation {
                id: bouncebehavior
                duration: 400
                easing.type: Easing.OutCubic

            }
    }
}
