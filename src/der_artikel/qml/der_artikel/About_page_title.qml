import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Title_bar {
    page_id: Manager.ABOUT_PAGE
    Image {
        id:icon
        source: "qrc:/res/resources/app.png"
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 2
        height:64
        width:height
        fillMode: Image.Stretch
    }

    Text {
        id: name
        text: "Der Artikel"
        anchors.left: icon.right
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        font.family: custom_regular.name
        color:color_palette.color_font_01
        font.pixelSize: 42
        horizontalAlignment: Text.AlignHCenter
    }
}
