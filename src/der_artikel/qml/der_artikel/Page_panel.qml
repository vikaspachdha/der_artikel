import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0
import QtGraphicalEffects 1.0

Item {
    Image {
        id: background_image
        anchors.fill: parent
        //anchors.margins: 8
        source:"qrc:/res/resources/alt_background_texture.png"
        fillMode: Image.Tile
        horizontalAlignment: Image.AlignLeft
        verticalAlignment: Image.AlignTop
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
