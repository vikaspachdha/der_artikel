import QtQuick 2.0

Item {
    property bool show: false
    Rectangle {
        id:rect
        anchors.fill: parent
        color:color_palette.color_font_02
        opacity:0
        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }
    }

   onShowChanged: {
       if(show === true) {
           rect.opacity = 0.9
       } else {
           rect.opacity = 0
       }
   }
}
