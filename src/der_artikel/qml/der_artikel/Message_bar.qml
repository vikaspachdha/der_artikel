import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0

Item {
    id:rootItem

    property alias title_text:msg_title.text
    property alias message_txt:msg_text.text
    property int type:0
    property bool hiding: false
    signal msgCompleted()

    Blanket {
        id:blanket
        anchors.fill: parent
    }

    Rectangle {
        id: msg_bar

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.top
        anchors.bottomMargin:8
        anchors.topMargin: -height/2

        radius:4
        height: 90
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
                case MessageBar.WARNING: return "qrc:/res/resources/warning.png";
                case MessageBar.ERROR: return "qrc:/res/resources/error.png";
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
            font.family: regular_font.name
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
                bottom: btnFrame.top
            }
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment:  Text.AlignVCenter
            font.family: regular_font.name
            color:color_palette.color_font_02
            font.pixelSize: 16
            elide:Text.ElideRight
            maximumLineCount: 2
            wrapMode: Text.WordWrap
        }

        Rectangle {
            id: btnFrame
            height: 32
            radius: 16
            color: color_palette.color_bg_01
            anchors {
                left: icon.right
                leftMargin: 8
                bottom: msg_bar.bottom
                bottomMargin: 4
                right: msg_bar.right
                rightMargin: 8
            }
            Button {
                id:accept_btn
                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                    leftMargin: 16
                }
                text_anchors.horizontalCenter: accept_btn.horizontalCenter
                onActivated: messageBarInstance.setAccepted(true)
            }

            Button {
                id:reject_btn
                anchors {
                    right: parent.right
                    rightMargin: 16
                    verticalCenter: parent.verticalCenter
                }
                text_anchors.horizontalCenter: reject_btn.horizontalCenter
                onActivated: messageBarInstance.setAccepted(false)
            }
        }

        states: [
            State {
                name: "show_message"
                AnchorChanges { target: msg_bar; anchors.top: rootItem.verticalCenter;anchors.bottom: undefined}
            },
            State {
                name: "hide_message"
                AnchorChanges { target: msg_bar; anchors.bottom: rootItem.top;anchors.top: undefined}
            }
        ]

        transitions: Transition {
            AnchorAnimation {
                id: msg_animation
                duration: settings.message_anim_time
                easing.type: Easing.OutCubic
            }
            onRunningChanged: {
                if(hiding) {
                    rootItem.msgCompleted()
                }
            }
        }

    }

    Timer {
        id:close_timer
        onTriggered: {
            closeMessage()
            hiding = false;
        }
    }

    function showMessage(title,msg,duration,msg_type,accept_str,reject_str)
    {
        rootItem.title_text=title
        rootItem.message_txt=msg
        rootItem.type = msg_type==null ? MessageBar.INFO : msg_type



        if(duration == null) {
            close_timer.interval = msg_animation.duration + 1200
            close_timer.start()
        } else if (duration === -1) {
            close_timer.interval = 0
        } else {
            close_timer.interval = msg_animation.duration + duration
            close_timer.start()
        }

        if(accept_str == null && reject_str == null) {
            btnFrame.visible = false
        } else {
            btnFrame.visible = true
            if(accept_str == null) {
                accept_btn.visible = false;
            } else {
                accept_btn.visible = true
                accept_btn.buttonText = accept_str;
            }

            if(reject_str == null) {
                reject_btn.visible = false;
            } else {
                reject_btn.visible = true
                reject_btn.buttonText = reject_str;
            }
        }

        blanket.showBlanket = true
        msg_bar.state = "show_message"
    }

    function closeMessage()
    {
        hiding = true;
        msg_bar.state = "hide_message"
        blanket.showBlanket = false
    }
}
