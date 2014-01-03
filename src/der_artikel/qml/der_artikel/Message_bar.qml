import QtQuick 2.0
import QtQuick.Controls 1.0

Rectangle {
    id: msg_bar
    property alias title_text:msg_title.text
    property alias message_txt:msg_text.text
    property alias msg_duration:pause_anim.duration
    property int type:0

    signal msgCompleted()

    y: -msg_bar.parent.height
    radius:4
    gradient: Gradient {
        GradientStop {position: 0  ;color: color_palette.color_btn_02}
        GradientStop {position: 0.5;color: color_palette.color_btn_01}
        GradientStop {position: 1;color: color_palette.color_btn_01}
    }

    Image {
        id: icon
        height:64
        width:height
        anchors {
            left: msg_bar.left
            leftMargin: 4
            verticalCenter: parent.verticalCenter
        }
        source: {
            switch(msg_bar.type) {
            case 1: return "qrc:/res/resources/warning.png";
            case 2: return "qrc:/res/resources/error.png";
            default: return "qrc:/res/resources/information.png";
            }
        }
    }

    Text {
        id: msg_title
        height: msg_bar.height * 0.40
        anchors {
            left: icon.right
            top: msg_bar.top
            right: msg_bar.right
        }
        font.family: custom_regular.name
        color:color_palette.color_font_02
        font.pixelSize: 20
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment:  Text.AlignVCenter
    }

    Text {
        id: msg_text
        height: msg_bar.height * 0.40
        anchors {
            left: icon.right
            top: msg_title.bottom
            right: msg_bar.right
            bottom: msg_bar.bottom
        }
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment:  Text.AlignVCenter
        font.family: custom_regular.name
        color:color_palette.color_font_02
        font.pixelSize: 16
        elide:Text.ElideRight
        maximumLineCount: 2
        wrapMode: Text.WordWrap
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
        onStopped: msg_bar.msgCompleted()
    }

    function showMessage(title,msg,duration,msg_type)
    {
        msg_bar.title_text=title
        msg_bar.message_txt=msg
        msg_bar.msg_duration = duration || 1200
        msg_bar.type = msg_type || 0
        animation.start()
    }

}
