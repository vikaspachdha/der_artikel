import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: root_item
    property var pageId
    y: manager.current_page === pageId ? 4 : -height-4
    height:60
    anchors{left:parent.left;right:parent.right}
    Behavior on y {
        NumberAnimation { duration:400 }
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
