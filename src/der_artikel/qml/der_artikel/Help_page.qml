import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0

Page {
    page_id:Manager.HELP_PAGE

    Rectangle {
        id: background
        anchors.fill: parent
        color:color_palette.color_bg_01
        radius: 4
    }

    Loader {
        id:loader
        anchors.fill: background
        source: help_page_instance.sub_page
    }
}
