import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0

Title_bar {
    page_id: Manager.HELP_PAGE

    Text {
        id: name
        text: help_page_instance.title
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: custom_regular.name
        color:color_palette.color_font_01
        font.pixelSize: 42
    }
}
