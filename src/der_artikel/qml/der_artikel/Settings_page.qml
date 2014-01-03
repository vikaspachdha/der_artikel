import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Page {
    id:root
    page_id:Manager.SETTINGS_PAGE

    Rectangle {
        id: background
        anchors.fill: parent
        color:color_palette.color_bg_01
        radius: 4
    }

    Loader {
        id:loader
        anchors.fill: background
        source: settings_page_instance.sub_page
    }
}
