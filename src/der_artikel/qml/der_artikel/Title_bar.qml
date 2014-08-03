import QtQuick 2.1
import QtGraphicalEffects 1.0

Item {
    id: title
    property int page_id
    y:-height-4
    height:72
    anchors{left:parent.left;right:parent.right}
    Behavior on y {
        SequentialAnimation {
            PauseAnimation { id:animPause }
            NumberAnimation { duration:200; easing.type: Easing.InOutElastic; easing.amplitude: 2.0; easing.period: 2.0}
            onRunningChanged: {
                if(running===true ) {
                    // Animation starting
                    if(manager.current_page === page_id) {
                        animPause.duration=0
                    } else {
                        animPause.duration=300
                    }
                } else {
                    // Animation stopped
                    if(manager.current_page !== page_id) {
                        title.destroy()
                    }
                }
            }
        }
    }

    Connections {
        target:manager
        onCurrentPageChanged: {
            y = manager.current_page === page_id ? 4 : -height-4
        }
    }

    Rectangle {
        id: background_image
        anchors.fill: parent
        radius:6
        color:color_palette.color_bg_01
    }

    DropShadow {
        anchors.fill: background_image
        visible: settings.enable_effects
        horizontalOffset: 2
        verticalOffset: 4
        radius: 0
        spread: 0.3
        samples: 16
        color: color_palette.shadow_color
        source: background_image
    }

    Component.onCompleted: {
        manager.setTitleItem(page_id,title)
        y = 4
    }
}
