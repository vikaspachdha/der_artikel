import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: startup_screen
    anchors.fill: parent
    anchors.margins: 0
    property int startup_time: 3000

    Behavior on anchors.margins {
        SequentialAnimation {
            NumberAnimation {
                duration:300;
            }
            onRunningChanged: {
                if(!running) {
                    startup_screen.visible = false
                    startup_screen.destroy()
                }
            }
        }
    }

    Behavior on anchors.bottomMargin {
        SequentialAnimation {
            NumberAnimation {
                duration:300;
            }
        }
    }

    Rectangle {
        id: background_rect
        anchors.fill: parent
        color:cp_blue.colorBg01
    }

    DropShadow {
        anchors.fill: background_rect
        horizontalOffset: 2
        verticalOffset: 4
        radius: 0
        spread: 0.3
        samples: 16
        color: "#66000000"
        source: background_rect
    }

    Text {
        id: name
        text: qsTr("Der Artikel")
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: custom_regular.name
        color:cp_blue.colorf01
        font.pixelSize: 42
    }

    Timer {
        id: hide_timer
        interval: startup_time
        onTriggered: {
            background_rect.radius=6
            startup_screen.anchors.bottomMargin = startup_screen.parent.height - 76
            startup_screen.anchors.margins = 4
        }
    }

    Component.onCompleted: {
        hide_timer.start()
    }
}
