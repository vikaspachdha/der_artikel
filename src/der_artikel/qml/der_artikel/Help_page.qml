import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Page {
    page_id:Manager.HELP_PAGE

    Rectangle {
        id: background
        anchors.fill: parent
        color:cp_blue.colorBtn02
        radius: 4
    }

    Loader {
        id:loader
        anchors.fill: background
        source: help_page
    }
}
