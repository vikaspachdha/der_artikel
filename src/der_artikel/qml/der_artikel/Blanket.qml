import QtQuick 2.0

Item {
    property bool show: false
    Rectangle {
        id:rect
        anchors.fill: parent
        color:color_palette.blanket_color
        opacity:0
        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }
    }

    MouseArea {
        anchors.fill: parent
        visible: show
    }

   onShowChanged: {
       if(show === true) {
           rect.opacity = 0.7
       } else {
           rect.opacity = 0
       }
   }
}
