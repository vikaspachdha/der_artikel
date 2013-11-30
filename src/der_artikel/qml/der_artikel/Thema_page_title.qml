import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Title_bar {

    y: manager.current_page === Manager.THEMA_PAGE ? 0 : -height
    Behavior on y {
        NumberAnimation { duration:400 }
    }

    Image {
        id: page_icon
        width: height
        anchors {
            top:parent.top
            left:parent.left
            bottom: parent.bottom
            margins:12
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
            top:parent.top
            left:page_icon.right
            leftMargin: 12
            topMargin: 8
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
            leftMargin: 12
        }
        font.pixelSize: 12
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignTop
    }
}
