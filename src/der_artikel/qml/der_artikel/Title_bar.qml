import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: root_item
    property var page_id
    y: manager.current_page === page_id ? 4 : -height-4
    height:60
    anchors{left:parent.left;right:parent.right}
    Behavior on y {
        SequentialAnimation {
            PauseAnimation { duration: (manager.current_page === page_id) ? 0 : 300}
            NumberAnimation { duration:200; easing.type: Easing.InOutElastic; easing.amplitude: 2.0; easing.period: 2.0}
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
        horizontalOffset: 2
        verticalOffset: 4
        radius: 0
        spread: 0.3
        samples: 16
        color: "#66000000"
        source: background_image
    }
}
