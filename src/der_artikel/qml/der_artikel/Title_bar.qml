import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: root_item

    Image {
        id: background_image
        anchors.fill: parent
        anchors.margins: 8
        source:"qrc:/res/resources/alt_background_texture.png"
        fillMode: Image.Tile
        horizontalAlignment: Image.AlignLeft
        verticalAlignment: Image.AlignTop
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


    clip: true

    Image {
        id: page_icon
        width: height
        anchors {
            top:background_image.top
            left:background_image.left
            bottom: background_image.bottom
            margins:4
        }
        source:"qrc:/res/resources/thema_icon.png"
        fillMode: Image.PreserveAspectFit
        horizontalAlignment: Image.AlignLeft
        verticalAlignment: Image.AlignTop
    }


    Text {
        id: heading_1
        text:"Thema : Wohnung"
        anchors {
            top:background_image.top
            left:page_icon.right
            leftMargin: 4
        }
        font.pixelSize: 14
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
            leftMargin: 4
        }
        font.pixelSize: 12
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignTop
    }

    Text {
        id: heading_3
        text:"00:00:00"
        anchors {
            top:heading_2.bottom
            left:page_icon.right
            right: background_image.right
            bottom: background_image.bottom
            rightMargin: 4
        }
        font.pixelSize: 18
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignRight
        verticalAlignment:  Text.AlignBottom
    }
}
