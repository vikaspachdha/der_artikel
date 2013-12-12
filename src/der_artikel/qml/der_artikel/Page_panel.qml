import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0
import QtGraphicalEffects 1.0

Item {
    property int page_id
    x: manager.current_page == page_id ? 8 : -width -12
    Behavior on x {
        SequentialAnimation {
            PauseAnimation
            {
                duration: (manager.current_page == page_id) ? 0 : 500
            }
            NumberAnimation { duration:400; easing.type: Easing.InOutElastic; easing.amplitude: 2.0; easing.period: 2.0}
        }
    }

    Rectangle {
        id: background_image
        anchors.fill: parent
        radius:6
        color:cp_blue.colorBg01
    }

    DropShadow {
        anchors.fill: background_image
        horizontalOffset: 4
        verticalOffset: 4
        radius: 0
        spread: 0.3
        samples: 16
        color: "#66000000"
        source: background_image
    }


}
