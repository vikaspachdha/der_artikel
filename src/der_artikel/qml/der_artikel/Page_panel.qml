import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0
import QtGraphicalEffects 1.0

Item {
    id:panel
    property int page_id
    x:-width -12
    width:100
    anchors {top:parent.top;bottom:parent.bottom}
    Behavior on x {
        SequentialAnimation {
            PauseAnimation { id:animPause}
            NumberAnimation { duration:200; easing.type: Easing.InOutElastic; easing.amplitude: 2.0; easing.period: 2.0}
            onRunningChanged: {
                if(running===true ) {
                    // Animation starting
                    if(manager.current_page == page_id) {
                        animPause.duration=0
                    } else {
                        animPause.duration=300
                    }
                } else {
                    // Animation stopped
                    if(manager.current_page !== page_id) {
                        panel.destroy()
                    }
                }
            }
        }
    }

    Connections {
        target:manager
        onCurrentPageChanged: {
            x = manager.current_page === page_id ? 8 : -width -12
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
        horizontalOffset: 4
        verticalOffset: 4
        radius: 0
        spread: 0.3
        samples: 16
        color: color_palette.shadow_color
        source: background_image
    }

    Component.onCompleted: {
        manager.setPanelItem(page_id,panel)
        x = 8;
    }
}
