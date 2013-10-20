import QtQuick 2.0
import QtQuick.Controls 1.0

Rectangle {
    id: msg_bar
    color:"blue"
    property alias title:msg_title.text
    property alias message:msg_text.text
    property alias animation_pause:pause_anim.duration
    property alias animate: animation.running
    y: -msg_bar.parent.height

    radius:4

    gradient: Gradient {
        GradientStop { position: 0.0; color: "#576495" }
        GradientStop { position: 0.05; color: "#6876B2" }
        //GradientStop { position: 0.33; color: "#6876B2" }
        GradientStop { position: 0.95; color: "#6876B2" }
        GradientStop { position: 1.0; color: "#576495" }
    }

    Rectangle {
        id: icon
        width:height
        color:"red"
        anchors {
            left: msg_bar.left
            top: msg_bar.top
            bottom: msg_bar.bottom
            margins: 4
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
        font.pointSize: height*0.8
        font.italic: true
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
        font.pointSize: height*0.30
        text:"message\nnext line"
    }

    SequentialAnimation {
        id: animation
        NumberAnimation {
            target: msg_bar
            property: "y"
            to: (msg_bar.parent.height - msg_bar.height)*0.5
            duration: 400
            easing.type: Easing.OutCubic

        }
        PauseAnimation { id: pause_anim; duration: 6000 }
        NumberAnimation {
            target: msg_bar
            property: "y"
            to: msg_bar.parent.height
            duration: 400
            easing.type: Easing.InCubic

        }
        NumberAnimation {
            target: msg_bar
            property: "y"
            to: -msg_bar.parent.height
            duration: 0
            easing.type: Easing.OutCubic

        }
    }

    states:[
        State {
            id:base
            AnchorChanges{
                target: msg_bar
                anchors.top: undefined
                anchors.verticalCenter: undefined
                anchors.bottom : msg_bar.parent.top
            }
        },
        State {
            id:middle
            AnchorChanges{
                target: msg_bar
                anchors.bottom: undefined
                anchors.top : undefined
                anchors.verticalCenter: msg_bar.parent.verticalCenter
            }
        },
        State {
            id:bottom
            AnchorChanges{
                target: msg_bar
                anchors.verticalCenter: undefined
                anchors.bottom: undefined
                anchors.top : msg_bar.parent.bottom
            }
        }

    ]

    function showMessage()
    {

    }



}
