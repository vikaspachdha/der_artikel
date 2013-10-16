import QtQuick 2.0

Rectangle {
    id: root_item
    gradient: Gradient {
              GradientStop { position: 0.0; color: "#8E9CA4" }
              GradientStop { position: 0.10; color: "#9CAFB8" }
              GradientStop { position: 0.90; color: "#9CAFB8" }
              GradientStop { position: 1.0; color: "#8E9CA4" }
          }
    clip: true

    Rectangle {
        id: page_icon
        width: height
        anchors {
            top:parent.top
            left:parent.left
            bottom: parent.bottom
            margins:4
        }
        color:"yellow"
    }


    Text {
        id: heading_1
        text:"Thema : Wohnung"
        anchors {
            top:root_item.top
            left:page_icon.right
            leftMargin: 4
        }
        font.pixelSize: 16
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignVCenter
    }

    Text {
        id: heading_2
        text:"Residential"
        anchors {
            top:heading_1.bottom
            left:page_icon.right
            bottom: root_item.bottom
            leftMargin: 4
        }
        font.pixelSize: 14
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignTop
    }

    Text {
        id: heading_3
        text:"00:00:00"
        anchors {
            top:root_item.top
            left:heading_1.right
            right:root_item.right
            bottom:root_item.bottom
            leftMargin: 16
        }
        font.pixelSize: 36
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignRight
        verticalAlignment:  Text.AlignVCenter
    }
}
