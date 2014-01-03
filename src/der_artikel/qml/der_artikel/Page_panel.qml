import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0
import QtGraphicalEffects 1.0

Item {
    id:panel
    property int page_id
    x: manager.current_page === page_id ? 8 : -width -12
    Behavior on x {
        SequentialAnimation {
            PauseAnimation { duration: (manager.current_page === page_id) ? 0 : 300}
            NumberAnimation { duration:200; easing.type: Easing.InOutElastic; easing.amplitude: 2.0; easing.period: 2.0}
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
    }


}
