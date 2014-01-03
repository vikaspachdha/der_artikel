import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Title_bar {
    page_id: Manager.HOME_PAGE
    Text {
        id: name
        text: qsTr("Der Artikel")
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: custom_regular.name
        color:color_palette.color_font_01
        font.pixelSize: 42
    }
}
